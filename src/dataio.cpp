#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <dlib/string.h>
#include <dlib/misc_api.h>
#include "dataio.h"


TextGridReader::TextGridReader (const std::string &textGridFile)
{
	readFile(textGridFile);
}

BoundVector TextGridReader::getBounds() const
{
	return m_bounds;
}

void TextGridReader::readFile(const std::string &textGridFile)
{
	try
	{
		// create a file-reading object
		std::ifstream fin;
		fin.open(textGridFile.c_str()); // open data file
		if (!fin.good())
		{
			throw dlib::error("[read_data_file] TextGrid input file not found!");
		}

		// container for string values
		std::string line, line_1, line_2;

		// process lines
		while(std::getline(fin, line))
		{
			if(line == "\"1\"")
			{
				m_bounds.push_back(atof(line_2.c_str()));
				m_bounds.push_back(atof(line_1.c_str()));
			}
			else if(!line.substr(0,1).compare("\""))
			{
				line = dlib::trim(line,"\"");
				if (checkDigits(line) && !line.empty())
				{
					m_bounds.push_back(atof(line_1.c_str()));
				}
			}

			// store temporary
			line_2 = line_1;
			line_1 = line;
		}
	}
	catch(...)
	{
		throw dlib::error("Wrong TextGrid File Format!");
	}
}

bool TextGridReader::checkDigits(const std::string &s)
{
  return s.find_first_not_of("0123456789") == std::string::npos;
}

PitchTierReader::PitchTierReader (const std::string &pitchTierFile)
{
	std::vector<std::string> tokens = dlib::split(pitchTierFile, ".");
	m_fileName = tokens[0];
	readFile(pitchTierFile);
}

TimeSignal PitchTierReader::getF0() const
{
	return m_f0;
}

std::string PitchTierReader::getFileName() const
{
	return m_fileName;
}

void PitchTierReader::readFile(const std::string &pitchTierFile)
{
	try
	{
		// create a file-reading object
		std::ifstream fin;
		fin.open(pitchTierFile.c_str()); // open data file
		if (!fin.good())
		{
			throw dlib::error("[read_data_file] PitchTier input file not found!");
		}

		// container for string values
		std::string line;
		std::vector<std::string> tokens;

		// ignore first three lines
		std::getline(fin, line);
		std::getline(fin, line);
		std::getline(fin, line);

		// following lines
		while(std::getline(fin, line))
		{
			tokens = dlib::split(line, "\t");
			double time = atof(tokens[0].c_str());
			double value = atof(tokens[1].c_str());
			Sample s = {time,hz2st(value)};
			m_f0.push_back(s);
		}
	}
	catch(...)
	{
		throw dlib::error("Wrong PitchTier File Format!");
	}
}

double PitchTierReader::hz2st (const double val)
{
	return 12*(std::log(val)/std::log(2));
}

void PitchTierWriter::writeF0(const TimeSignal &f0) const
{
	// create output file and write results to it
	unsigned K = f0.size();
	std::ofstream fout;
	fout.open(m_file.c_str());
	fout << std::fixed << std::setprecision(6);

	// write header
	fout << "\"ooTextFile\"" << std::endl;
	fout << "\"PitchTier\"" << std::endl;
	fout << 0 << " " << f0[K-1].time+0.1 << " " << K << std::endl;

	// write optimal f0
	for (int i=0; i<f0.size(); ++i)
	{
		fout << f0[i].time << "\t" << f0[i].value << std::endl;
	}
}

void GestureWriter::writeTargets(const Sample &onset, const TargetVector &targets) const
{
	// create output file and write results to it
	std::ofstream fout;
	fout.open(m_file.c_str());
	fout << std::fixed << std::setprecision(6);

	// write header
	fout << "<gestural_score>" << std::endl;
	fout << "\t<gesture_sequence type=\"f0-gestures\" unit=\"st\">" << std::endl;

	// write first two optimal target
	fout << "\t\t<gesture value=\"" 	<< onset.value
		 << "\" slope=\"" 			<< 0.000000
		 << "\" duration_s=\"" 		<< 0.010000
		 << "\" time_constant_s=\"" << 0.010000
		 << " neutral=\"0\" />"		<< std::endl;

	fout << "\t\t<gesture value=\"" 	<< targets[0].offset
		 << "\" slope=\"" 			<< targets[0].slope
		 << "\" duration_s=\"" 		<< targets[0].duration-0.01
		 << "\" time_constant_s=\"" << targets[0].tau/1000.0
		 << " neutral=\"0\" />"		<< std::endl;

	// write resulting optimal targets
	for (int i=1; i<targets.size(); ++i)
	{
		fout << "\t\t<gesture value=\"" 	<< targets[i].offset
			 << "\" slope=\"" 			<< targets[i].slope
			 << "\" duration_s=\"" 		<< targets[i].duration
			 << "\" time_constant_s=\"" << targets[i].tau/1000.0
			 << " neutral=\"0\" />"		<< std::endl;
	}

	// write tail
	fout << "\t</gesture_sequence>" << std::endl;
	fout << "</gestural_score>" << std::endl;
}

void CsvWriter::writeTargets(const Sample &onset, const TargetVector &targets) const
{
	// create output file and write results to it
	std::ofstream fout;
	fout.open(m_file.c_str());
	fout << std::fixed << std::setprecision(6);

	// write optimal onset
	fout << onset.time << "," << onset.value << std::endl;

	// write optimal targets
	for (int i=0; i<targets.size(); ++i)
	{
		fout << targets[i].slope << "," << targets[i].offset << "," << targets[i].tau << "," << targets[i].duration << std::endl;
	}
}

PlotRegion::PlotRegion (drawable_window& w) : zoomable_region(w,MOUSE_CLICK | MOUSE_WHEEL | KEYBOARD_EVENTS)
{
	enable_events();
}

PlotRegion::~PlotRegion ()
{
	disable_events();
	parent.invalidate_rectangle(rect);
}

void PlotRegion::setBounds(const BoundVector &bounds)
{
	m_bounds = bounds;
	parent.invalidate_rectangle(rect);
};

void PlotRegion::setOrigF0(const TimeSignal &f0)
{
	m_origF0 = f0;
	parent.invalidate_rectangle(rect);
}

void PlotRegion::setOptimalF0(const TimeSignal &f0)
{
	m_optF0 = f0;
	parent.invalidate_rectangle(rect);
}

void PlotRegion::setTargets(const TargetVector &targets)
{
	m_targets = targets;
	parent.invalidate_rectangle(rect);
}

void PlotRegion::draw (const canvas& c) const
{
	zoomable_region::draw(c);

	rectangle area = c.intersect(display_rect());
	if (area.is_empty() == true)
		return;

	if (enabled)
		fill_rect(c,display_rect(),255);
	else
		fill_rect(c,display_rect(),128);

	SignalStat scaler = {0,0,0,0};
	// draw bounds
	if (!m_bounds.empty())
	{
		scaler.minTime = m_bounds[0]-0.1;
		scaler.maxTime = m_bounds[m_bounds.size()-1]+0.1;
		for (int i = 0; i < m_bounds.size(); ++i)
		{
			double position = ((m_bounds[i]-scaler.minTime)/(scaler.maxTime-scaler.minTime))*width();
			point p(graph_to_gui_space(point(position,0)));
			point p2(graph_to_gui_space(point(position,height())));
			draw_line(c,p2,p ,rgb_pixel(0,0,0), area);
		}
	}

	// draw original f0
	if (!m_origF0.empty())
	{
		SignalStat stat = analyzeSignal(m_origF0);
		scaler.maxValue = stat.maxValue+5;
		scaler.minValue = stat.minValue-5;
		if (scaler.maxTime == 0.0)
		{
			scaler.maxTime = stat.maxTime;
			scaler.minTime = stat.minTime;
		}
		for (int i=0; i<m_origF0.size(); ++i)
		{
			double x = ((m_origF0[i].time-scaler.minTime)/(scaler.maxTime-scaler.minTime))*width();
			double y = ((m_origF0[i].value-scaler.minValue)/(scaler.maxValue-scaler.minValue))*height();
			draw_solid_circle(c, graph_to_gui_space(point(x,y)), 2, rgb_pixel(0,0,255));
		}
	}

	// draw optimal f0
	if(!m_optF0.empty())
	{
		for (int i=0; i<m_optF0.size(); ++i)
		{
			double x1 = ((m_optF0[i].time-scaler.minTime)/(scaler.maxTime-scaler.minTime))*width();
			double y1 = ((m_optF0[i].value-scaler.minValue)/(scaler.maxValue-scaler.minValue))*height();
			//double x2 = ((m_optF0[i+1].time-scaler.minTime)/(scaler.maxTime-scaler.minTime))*width();
			//double y2 = ((m_optF0[i+1].value-scaler.minValue)/(scaler.maxValue-scaler.minValue))*height();
			draw_solid_circle(c, graph_to_gui_space(point(x1,y1)), 1.5, rgb_pixel(100,200,100));
			//draw_line(c,point(x1,y1),point(x2,y2) ,rgb_pixel(255,0,0), area);
		}
	}

	// draw optimal targets
	if(!m_targets.empty())
	{
		double begin = m_optF0[0].time;
		double end = begin;
		for (int i=0; i<m_targets.size(); ++i)
		{
			begin = end;
			end = begin + m_targets[i].duration;
			double x1 = ((begin-scaler.minTime)/(scaler.maxTime-scaler.minTime))*width();
			double y1 = ((m_targets[i].offset-scaler.minValue)/(scaler.maxValue-scaler.minValue))*height();
			double x2 = ((end-scaler.minTime)/(scaler.maxTime-scaler.minTime))*width();
			double y2 = (((m_targets[i].offset + m_targets[i].slope*m_targets[i].duration)-scaler.minValue)/(scaler.maxValue-scaler.minValue))*height();
			draw_line(c,graph_to_gui_space(point(x1,y1)), graph_to_gui_space(point(x2,y2)) ,rgb_pixel(200,100,100), area);
		}
	}
}

SignalStat PlotRegion::analyzeSignal(const TimeSignal &f0) const
{
	std::vector<double> times, values;
	for (int i=0; i<f0.size(); ++i)
	{
		times.push_back(f0[i].time);
		values.push_back(f0[i].value);
	}

	SignalStat result;
	result.minTime = *std::min_element(times.begin(), times.end());
	result.maxTime = *std::max_element(times.begin(), times.end());
	result.minValue = *std::min_element(values.begin(), values.end());
	result.maxValue = *std::max_element(values.begin(), values.end());

	return result;
}

MainWindow::MainWindow() :
    colorBlack(0,0,0),
    colorWhite(255,255,255),
    colorMix(100,200,100),
    colorRed(255,0,0),
    colorGray(210,210,210),
	graph(*this),
	btnLoadTextGrid(*this),
	btnLoadPitchTier(*this),
	btnOptimize(*this),
	btnStoreGesture(*this),
    mbar(*this),
	recTargets(*this),
	recOptions(*this),
	recActions(*this),
	targetGrid(*this),
	searchGrid(*this),
	penaltyGrid(*this),
	searchSpaceGroup(*this),
	penaltyGroup(*this),
	tabs(*this),
	selOnset(*this),
	lbOnset(*this)
{
    set_title("Target Optimizer");

    // position the widget that is responsible for drawing the directed graph, the graph_drawer,
    // just below the mbar (menu bar) widget.
    graph.set_pos(15,mbar.bottom()+5);
    graph.set_min_zoom_scale(1.0);
    set_size(750,520);

    // register the event handlers with their respective widgets
    btnLoadTextGrid.set_click_handler(*this, &MainWindow::onButtonTextGridOpen);
    btnLoadPitchTier.set_click_handler(*this, &MainWindow::onButtonPitchTierOpen);
    btnOptimize.set_click_handler(*this, &MainWindow::onButtonOptimize);
    btnStoreGesture.set_click_handler(*this, &MainWindow::onButtonSaveAsGesture);

    // now set the text of some of our buttons and labels
    btnLoadTextGrid.set_name("Load TextGrid");
    btnLoadPitchTier.set_name("Load PitchTier");
    btnOptimize.set_name("Optimize");
    btnStoreGesture.set_name("Save as VTL Gesture");
    recTargets.set_name("Targets");
    recOptions.set_name("Options");
    recActions.set_name("Actions");
    lbOnset.set_text("Optimize Onset");

    // Now setup the tabbed display.  It will have two tabs, one for the search space
    // and for regularization
    tabs.set_number_of_tabs(2);
    tabs.set_tab_name(0,"Search Space");
    tabs.set_tab_name(1,"Regularization");
    searchSpaceGroup.add(searchGrid,0,0);
    penaltyGroup.add(penaltyGrid,0,0);
    tabs.set_tab_group(0,searchSpaceGroup);
    tabs.set_tab_group(1,penaltyGroup);

    // Now setup the menu bar.  We will have two menus.  A File and Help menu.
    mbar.set_number_of_menus(2);
    mbar.set_menu_name(0,"File",'F');
    mbar.set_menu_name(1,"Help",'H');

    // add the entries to the File menu.
    mbar.menu(0).add_menu_item(menu_item_text("Open TextGrid", *this, &MainWindow::onButtonTextGridOpen, 'T'));
    mbar.menu(0).add_menu_item(menu_item_text("Open PitchTier", *this, &MainWindow::onButtonPitchTierOpen, 'P'));
    mbar.menu(0).add_menu_item(menu_item_separator());
    mbar.menu(0).add_menu_item(menu_item_text("Optimize", *this, &MainWindow::onButtonOptimize, 'O'));
    mbar.menu(0).add_menu_item(menu_item_separator());
    mbar.menu(0).add_menu_item(menu_item_text("Save As Gesture",*this, &MainWindow::onButtonSaveAsGesture, 'G'));
    mbar.menu(0).add_menu_item(menu_item_text("Save As csv",*this, &MainWindow::onMenuSaveAsCsv, 'c'));
    mbar.menu(0).add_menu_item(menu_item_text("Save As PitchTier",*this, &MainWindow::onMenuSaveAsPitchTier, 'i'));
    mbar.menu(0).add_menu_item(menu_item_separator());
    mbar.menu(0).add_menu_item(menu_item_text("Quit",   *this, &MainWindow::onMenuFileQuit,    'Q'));

    // Add the entries to the Help menu.
    mbar.menu(1).add_menu_item(menu_item_text("Help",   *this, &MainWindow::onMenuFileHelp,'H'));
    mbar.menu(1).add_menu_item(menu_item_text("About",  *this, &MainWindow::onMenuFileAbout,'A'));

    // call our helper functions and window resize event to get the widgets
    // to all arrange themselves correctly in our window.
    noOptimizationPerformed();
    on_window_resized();
}

MainWindow::~MainWindow()
{
    close_window();
}

void MainWindow::noOptimizationPerformed ()
{
    btnOptimize.disable();
    btnStoreGesture.disable();
    searchGrid.set_grid_size(4,2);
    penaltyGrid.set_grid_size(5,2);
    targetGrid.set_grid_size(4,1);
    targetGrid.disable();

    selOnset.set_checked();
    searchGrid.set_border_color(colorBlack);
    searchGrid.set_text(1,0,"slope:  0.0 [st/s] +/- ");
    searchGrid.set_text(2,0,"offset: mean(f0) [st] +/- ");
    searchGrid.set_text(3,0,"tau:    15.0 [ms] +/- ");
    searchGrid.set_background_color(1,0,rgb_pixel(200,250,250));
    searchGrid.set_background_color(2,0,rgb_pixel(200,250,250));
    searchGrid.set_background_color(3,0,rgb_pixel(200,250,250));
    searchGrid.set_editable(1,0,false);
    searchGrid.set_editable(2,0,false);
    searchGrid.set_editable(3,0,false);
    searchGrid.set_column_width(0,150);
    searchGrid.set_text(1,1,"50.0");
    searchGrid.set_text(2,1,"20.0");
    searchGrid.set_text(3,1,"5.0");
    searchGrid.set_column_width(1,50);
    searchGrid.set_text(0,0,"parameter");
    searchGrid.set_text(0,1,"value");
    searchGrid.set_background_color(0,0,rgb_pixel(170,220,220));
    searchGrid.set_background_color(0,1,rgb_pixel(170,220,220));
    searchGrid.set_editable(0,0,false);
    searchGrid.set_editable(0,1,false);

    penaltyGrid.set_border_color(colorBlack);
    penaltyGrid.set_text(1,0,"lambda");
    penaltyGrid.set_text(2,0,"weight-slope");
    penaltyGrid.set_text(3,0,"weight-offset");
    penaltyGrid.set_text(4,0,"weight-tau");
    penaltyGrid.set_background_color(1,0,rgb_pixel(200,250,250));
    penaltyGrid.set_background_color(2,0,rgb_pixel(200,250,250));
    penaltyGrid.set_background_color(3,0,rgb_pixel(200,250,250));
    penaltyGrid.set_background_color(4,0,rgb_pixel(200,250,250));
    penaltyGrid.set_editable(1,0,false);
    penaltyGrid.set_editable(2,0,false);
    penaltyGrid.set_editable(3,0,false);
    penaltyGrid.set_editable(4,0,false);
    penaltyGrid.set_column_width(0,150);
    penaltyGrid.set_text(1,1,"0.0");
    penaltyGrid.set_text(2,1,"10.0");
    penaltyGrid.set_text(3,1,"5.0");
    penaltyGrid.set_text(4,1,"1.0");
    penaltyGrid.set_column_width(1,50);
    penaltyGrid.set_text(0,0,"parameter");
    penaltyGrid.set_text(0,1,"value");
    penaltyGrid.set_background_color(0,0,rgb_pixel(170,220,220));
    penaltyGrid.set_background_color(0,1,rgb_pixel(170,220,220));
    penaltyGrid.set_editable(0,0,false);
    penaltyGrid.set_editable(0,1,false);

}

void MainWindow::on_window_resized ()
{
    // when you override any of the drawable_window events you have to make sure you
    // call the drawable_window's version of them because it needs to process
    // the events as well.  So we do that here.
    drawable_window::on_window_resized();

    // The rest of this function positions the widgets on the window
    unsigned long width,height;
    get_size(width,height);

    // Don't do anything if the user just made the window too small.  That is, leave
    // the widgets where they are.
    if (width < 500 || height < 350)
        return;

    // Set the size of the probability tables and the drawing area for the graph
    graph.set_size(0.97*width,0.55*height-+mbar.height());
    searchGrid.set_size(0.3*width,0.25*height);
    penaltyGrid.set_size(0.3*width,0.25*height);
    targetGrid.set_size(0.35*width,0.25*height);
    // tell the tabbed display to make itself just the right size to contain
    // the two probability tables.
    tabs.fit_to_contents();


    // Now position all the widgets in the window.  Note that much of the positioning
    // is relative to other widgets.  This part of the code I just figured out by
    // trying stuff and rerunning the program to see if it looked nice.

    btnLoadTextGrid.set_pos(0.35*width+15,graph.bottom()+30);
	btnLoadPitchTier.set_pos(0.35*width+15,graph.bottom()+60);
	btnOptimize.set_pos(0.35*width+15,graph.bottom()+90);
	btnStoreGesture.set_pos(0.35*width+15,graph.bottom()+120);
	selOnset.set_pos(15,graph.bottom()+30);
	targetGrid.set_pos(0.6*width+15,graph.bottom()+30);
	tabs.set_pos(15,graph.bottom()+50);
	lbOnset.set_pos(selOnset.right()+10, selOnset.top());

	btnLoadTextGrid.set_size(btnStoreGesture.get_rect().width(), btnStoreGesture.get_rect().height());
	btnLoadPitchTier.set_size(btnStoreGesture.get_rect().width(), btnStoreGesture.get_rect().height());
	btnOptimize.set_size(btnStoreGesture.get_rect().width(), btnStoreGesture.get_rect().height());


    // Tell the named rectangle to position itself such that it fits around the
    // tabbed display that contains the probability tables and the label at the top of the
    // screen.
	recOptions.wrap_around(selOnset.get_rect()+tabs.get_rect());
	recTargets.wrap_around(targetGrid.get_rect());
	recActions.wrap_around(btnLoadTextGrid.get_rect()+btnStoreGesture.get_rect());
	//graph.disable();
}

void MainWindow::openTextGrid (const std::string& fileName)
{
    try
    {
		// process TextGrid input
		TextGridReader tgreader (fileName);
		m_bounds = tgreader.getBounds();
		graph.setBounds(m_bounds);
    }
    catch (...)
    {
        message_box("Error", "Unable to load TextGrid file " + fileName);
    }
}

void MainWindow::openPitchTier (const std::string& fileName)
{
    try
    {
		// process PitchTier input
		PitchTierReader ptreader (fileName);
		m_origF0 = ptreader.getF0();
		graph.setOrigF0(m_origF0);
        set_title("Target Optimizer - " + left_substr(right_substr(fileName,"\\/"), "."));
    }
    catch (...)
    {
        message_box("Error", "Unable to load TextGrid file " + fileName);
    }
}

void MainWindow::onButtonTextGridOpen ()
{
    // display a file chooser window and when the user choses a file
    // call the on_open_file_selected() function
    open_existing_file_box(*this, &MainWindow::openTextGrid);
    if (!m_origF0.empty())
    {
    	onReadyForOptimize();
    }
}

void MainWindow::onButtonPitchTierOpen ()
{
    // display a file chooser window and when the user choses a file
    // call the on_open_file_selected() function
    open_existing_file_box(*this, &MainWindow::openPitchTier);
    if (!m_bounds.empty())
    {
    	onReadyForOptimize();
    }
}

void MainWindow::onReadyForOptimize ()
{
	btnOptimize.enable();
}

void MainWindow::onButtonOptimize ()
{
	// main task

	ParameterSet parameters = readParameters();
	OptimizationProblem problem (parameters, m_origF0, m_bounds);
	BobyqaOptimizer optimizer;
	optimizer.optimize(problem);
	m_optTarget = problem.getPitchTargets();
	m_optF0 = problem.getModelF0();
	m_optOnset = problem.getOnset();
	graph.setTargets(m_optTarget);
	graph.setOptimalF0(m_optF0);

	unblockMainWindow();
	std::ostringstream msg;
	msg << "Optimization successful!\nRMSE = " << problem.getRootMeanSquareError() << "\nCORR = " << problem.getCorrelationCoefficient();
	message_box("Information", msg.str());
}

ParameterSet MainWindow::readParameters()
{
	//calculate mean f0
	double meanF0 = 0.0;
	for (int i=0; i<m_origF0.size(); ++i)
	{
		meanF0 += m_origF0[i].value;
	}
	meanF0 /= m_origF0.size();

	ParameterSet parameters;
	try
	{
		parameters.deltaSlope = atof(searchGrid.text(1,1).c_str());
		parameters.deltaOffset = atof(searchGrid.text(2,1).c_str());
		parameters.deltaTau = atof(searchGrid.text(3,1).c_str());
		parameters.weightSlope = atof(penaltyGrid.text(2,1).c_str());
		parameters.weightOffset = atof(penaltyGrid.text(3,1).c_str());
		parameters.weightTau = atof(penaltyGrid.text(4,1).c_str());
		parameters.lambda = atof(penaltyGrid.text(1,1).c_str());
		parameters.meanSlope = 0.0;
		parameters.meanOffset = meanF0;
		parameters.meanTau = 15.0;
	}
	catch(...)
	{
		throw dlib::error("Wrong Option Format. Please Enter a number!");
	}

	return parameters;
}

// This event is called when the user choses which file to save the graph to
void MainWindow::onSaveFileGesture (const std::string& fileName)
{
    GestureWriter gwriter (fileName + ".ges");
    gwriter.writeTargets(m_optOnset, m_optTarget);
}

// This event is called when the user selects from the menu bar File->Save As
void MainWindow::onButtonSaveAsGesture ()
{
    save_file_box(*this, &MainWindow::onSaveFileGesture);
}

// This event is called when the user choses which file to save the graph to
void MainWindow::onSaveFileCsv (const std::string& fileName)
{
	CsvWriter cwriter (fileName + ".csv");
	cwriter.writeTargets(m_optOnset, m_optTarget);
}

// This event is called when the user selects from the menu bar File->Save As
void MainWindow::onMenuSaveAsCsv ()
{
    save_file_box(*this, &MainWindow::onSaveFileCsv);
}

// This event is called when the user choses which file to save the graph to
void MainWindow::onSaveFilePitchTier(const std::string& fileName)
{
	PitchTierWriter pwriter (fileName + "-tam.PitchTier");
	pwriter.writeF0(m_optF0);
}

// This event is called when the user selects from the menu bar File->Save As
void MainWindow::onMenuSaveAsPitchTier ()
{
    save_file_box(*this, &MainWindow::onSaveFilePitchTier);
}

void MainWindow::blockMainWindow()
{
	tabs.disable();
	targetGrid.disable();
	btnLoadTextGrid.disable();
	btnLoadPitchTier.disable();
	btnOptimize.disable();
	btnStoreGesture.disable();
	graph.disable();
	mbar.disable();
}

void MainWindow::unblockMainWindow()
{
	tabs.enable();
	targetGrid.enable();
	btnLoadTextGrid.enable();
	btnLoadPitchTier.enable();
	btnOptimize.enable();
	btnStoreGesture.enable();
	graph.enable();
	mbar.enable();
}

void MainWindow::onMenuFileQuit()
{
	close_window();
}

void MainWindow::onMenuFileHelp()
{
	message_box("Help",
	                "To create new nodes right click on the drawing area.\n"
	                "To create edges select the parent node and then shift+left click on the child node.\n"
	                "To remove nodes or edges select them by left clicking and then press the delete key.");
}

void MainWindow::onMenuFileAbout()
{
    message_box("About","This application is the GUI front end to the dlib C++ Library's\n"
                "Bayesian Network inference utilities\n\n"
                "Version 1.2\n\n"
                "See http://dlib.net for updates");
}
