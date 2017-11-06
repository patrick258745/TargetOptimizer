#include <stdlib.h>
#include <fstream>
#include <dlib/string.h>
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
    set_size(750,520);

    // register the event handlers with their respective widgets
//    btn_calculate.set_click_handler              (*this, &main_window::recalculate_probabilities);
//    cpt_grid.set_text_modified_handler           (*this, &main_window::on_cpt_grid_modified);
//    graph_drawer.set_graph_modified_handler      (*this, &main_window::on_graph_modified);
//    graph_drawer.set_node_deleted_handler        (*this, &main_window::on_node_deleted);
//    graph_drawer.set_node_deselected_handler     (*this, &main_window::on_node_deselected);
//    graph_drawer.set_node_selected_handler       (*this, &main_window::on_node_selected);
//    sel_node_evidence.set_text_modified_handler  (*this, &main_window::on_sel_node_evidence_modified);
//    sel_node_is_evidence.set_click_handler       (*this, &main_window::on_evidence_toggled);
//    sel_node_num_values.set_text_modified_handler(*this, &main_window::on_sel_node_num_values_modified);
//    sel_node_text.set_text_modified_handler      (*this, &main_window::on_sel_node_text_modified);
    btnLoadTextGrid.set_click_handler(*this, &MainWindow::onButtonTextGridOpen);
    btnLoadPitchTier.set_click_handler(*this, &MainWindow::onButtonPitchTierOpen);
    btnOptimize.set_click_handler(*this, &MainWindow::onButtonOptimize);

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
//    mbar.menu(0).add_menu_item(menu_item_text("Open",   *this, &main_window::on_menu_file_open,    'O'));
//    mbar.menu(0).add_menu_item(menu_item_separator());
//    mbar.menu(0).add_menu_item(menu_item_text("Save",   *this, &main_window::on_menu_file_save,    'S'));
//    mbar.menu(0).add_menu_item(menu_item_text("Save As",*this, &main_window::on_menu_file_save_as, 'a'));
//    mbar.menu(0).add_menu_item(menu_item_separator());
//    mbar.menu(0).add_menu_item(menu_item_text("Quit",   *this, &main_window::on_menu_file_quit,    'Q'));
//
//    // Add the entries to the Help menu.
//    mbar.menu(1).add_menu_item(menu_item_text("Help",   *this, &main_window::on_menu_help_help,    'e'));
//    mbar.menu(1).add_menu_item(menu_item_text("About",  *this, &main_window::on_menu_help_about,   'A'));


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
    targetGrid.set_size(0.35*width,0.22*height);
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
	graph.disable();
}

void MainWindow::openTextGrid (const std::string& fileName)
{
    try
    {
		// process TextGrid input
		TextGridReader tgreader (fileName);
		m_bounds = tgreader.getBounds();
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
