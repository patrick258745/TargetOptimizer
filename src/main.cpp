#include <iostream>
#include <string>
#include <dlib/cmd_line_parser.h>
#include "model.h"

int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		// ********** open GUI **********


		// Normally, if you built this application on MS Windows in Visual Studio you
		// would see a black console window pop up when you ran it.  The following
		// #pragma directives tell Visual Studio to not include a console window along
		// with your application.  However, if you prefer to have the console pop up as
		// well then simply remove these #pragma statements.
		#ifdef _MSC_VER
		#   pragma comment( linker, "/entry:mainCRTStartup" )
		#   pragma comment( linker, "/SUBSYSTEM:WINDOWS" )
		#endif
	}
	else
	{
		// ********** command line parsing **********
		try
		{
			dlib::command_line_parser parser;

			// command line options
			parser.add_option("h","Display this help message.");
			parser.set_group_name("Output Options");
			parser.add_option("g","Choose for VTL gesture file.");
			parser.add_option("c","Choose for csv table file.");
			parser.add_option("p","Choose for PitchTier file.");
			parser.set_group_name("Additional Options");
			parser.add_option("m-range","Specify search space for slope parameter.",1);
			parser.add_option("b-range","Specify search space for offset parameter.",1);
			parser.add_option("t-range","Specify search space for time constant parameter.",1);
			parser.add_option("m-weight","Specify regularization weight for slope parameter.",1);
			parser.add_option("b-weight","Specify regularization weight for offset parameter.",1);
			parser.add_option("t-weight","Specify regularization weight for time constant parameter.",1);

			// parse command line
			parser.parse(argc,argv);

			// check command line options
			const char* one_time_opts[] = {"h", "g", "c", "p", "m-range", "b-range", "t-range", "m-weight", "b-weight", "t-weight"};
			parser.check_one_time_options(one_time_opts);
			parser.check_option_arg_range("m-range", 0.0, 1000.0);
			parser.check_option_arg_range("b-range", 0.0, 1000.0);
			parser.check_option_arg_range("t-range", 0.0, 1000.0);
			parser.check_option_arg_range("m-weight", 0.0, 1e9);
			parser.check_option_arg_range("b-weight", 0.0, 1e9);
			parser.check_option_arg_range("t-weight", 0.0, 1e9);
		}
		catch (std::exception& e)
		{
			std::cerr << "[main] Program was terminated because an error occurred!\n" << e.what() << std::endl;
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}
}


























		// process command line options
		if (parser.option("h"))
		{
			std::cout << "Usage: TargetOptimizer { <options> | <arg> } TextGrid-file PitchTier-file\n";
			parser.print_options();
			return EXIT_SUCCESS;
		}

        if (!parser.option("s") && !parser.option("r"))
        {
            std::cout << "Error in command line:\n   You must specify either the s option or the r option.\n";
            std::cout << "\nTry the -h option for more information." << std::endl;
            return EXIT_FAILURE;
        }

        if (parser.option("in"))
		{
        	inputFile = parser.option("in").argument();
		}
		else
		{
			std::cout << "Error in command line:\n   You must specify an input file.\n";
			std::cout << "\nTry the -h option for more information." << std::endl;
			return EXIT_FAILURE;
		}

        if (parser.option("out"))
		{
        	outputFile = parser.option("out").argument();
		}
		else
		{
			std::cout << "Error in command line:\n   You must specify an output file.\n";
			std::cout << "\nTry the -h option for more information." << std::endl;
			return EXIT_FAILURE;
		}

		/********** main script **********/
		target_v optParams;
		std::vector<bound_s> searchSpace;
		PraatFileIo praatFiles;
		QtaErrorFunction qtaError;
		qtaError.set_lambda(get_option(parser,"l",0.0));
		Optimizer paramSearch;

		// get optimal qta parameters
		if (parser.option("s"))
		{
			praatFiles.read_praat_file(qtaError, searchSpace, inputFile);
			qtaError.set_search_bounds(searchSpace);
			paramSearch.optimize(optParams, qtaError, searchSpace);
		}
		else
		{
			praatFiles.read_praat_file(qtaError, optParams, inputFile);
		}

		// save results to praat file
		praatFiles.write_praat_file(qtaError, optParams, outputFile);

		/*********************************/
	}
	catch (std::exception& e)
	{
		std::cerr << "[main] Program was terminated because an error occurred!\n" << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


