#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <unistd.h>


struct command_line_args {
    std::string test_input_dir;
    std::string correct_args;
    std::string target_args;
    std::string input_args;
};

command_line_args *parse_command_line_args(int argc, char* argv[]) {
    command_line_args *args = new command_line_args;

    int opt;
    while ((opt = getopt(argc, argv, "i:c:t:a")) != -1) {
        switch (opt) {
            case 'i':
                args->test_input_dir = optarg;
                break;
            case 'c':
                args->correct_args = optarg;
                break;
            case 't':
                args->target_args = optarg;
                break;
            case 'a':
                if (optarg == NULL) break;
                args->input_args = optarg;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -i test_input_dir -c \"correct_args\" -t \"target_args\" -a args" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    return args;
}

bool compile_and_run(const std::string &solution_path, const std::string &student_path, const std::string& args, const std::string& input_dir) {
    // Compile solution
    if (std::system(solution_path.c_str()) != 0) {
        std::cerr << "Error compiling solution" << std::endl;
        return false;
    }

    // Compile student's code
    if (std::system(student_path.c_str()) != 0) {
        std::cerr << "Error compiling student" << std::endl;
        return false;
    }

    // Prepare the input files
    std::vector<std::string> input_files;
    std::string input_path = input_dir + "/";
    for (const auto& entry : std::filesystem::directory_iterator(input_path)) {
        std::cout << entry.path().string() << std::endl;
        input_files.push_back(entry.path().string());
    }

    // Run solution
    std::string solution_output = "";
    for (const std::string& input_file : input_files) {
        FILE* solution_output_file = popen(("./solution " + args + " < " + input_file).c_str(), "r");
        if (solution_output_file) {
            char buffer[128];
            while (fgets(buffer, sizeof(buffer), solution_output_file) != nullptr) {
                solution_output += buffer;
            }
            pclose(solution_output_file);
        }
    }

    // Run student's code
    std::string student_output = "";
    for (const std::string& input_file : input_files) {
        FILE* student_output_file = popen(("./student " + args + " < " + input_file).c_str(), "r");
        if (student_output_file) {
            char buffer[128];
            while (fgets(buffer, sizeof(buffer), student_output_file) != nullptr) {
                student_output += buffer;
            }
            pclose(student_output_file);
        }
    }

    std::cout << "Solution output: " << solution_output << std::endl;
    std::cout << "Student output: " << student_output << std::endl;

    // Compare outputs
    if (solution_output == student_output) {
        std::cout << "Student's code is correct." << std::endl;
        return true;
    } else {
        std::cout << "Student's code is incorrect." << std::endl;
        return false;
    }
}

int main(int argc, char* argv[]) {
    command_line_args *cmd_args = parse_command_line_args(argc, argv);

    if (compile_and_run(cmd_args->correct_args, cmd_args->target_args, cmd_args->input_args, cmd_args->test_input_dir)) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Incorrect" << std::endl;
    }

    delete cmd_args;

    return 0;
}