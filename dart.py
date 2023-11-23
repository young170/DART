import subprocess
import sys

class CppProgram:
    def __init__(self, source_code, output_binary):
        self.source_code = source_code
        self.output_binary = output_binary

    def compile(self):
        compile_command = f"g++ {self.source_code} -o {self.output_binary}"
        subprocess.run(compile_command, shell=True, check=True)

    def run(self, program_args):
        args = ' '.join(program_args) if program_args else ''
        run_command = f"./{self.output_binary} {args}"
        result = subprocess.run(run_command, text=True, capture_output=True)
        return result.stdout.strip()

class TestRunner:
    def __init__(self):
        self.test_results = []

    def run_test_case(self, solution_program, test_program, input_data):
        solution_output = solution_program.run(input_data)
        test_output = test_program.run(input_data)

        result = solution_output == test_output
        self.test_results.append(result)
        return result

    def get_test_results(self):
        return self.test_results

class CppGrader:
    def __init__(self, solution_program, program_to_test, solution_program_arg=None, program_to_test_arg=None, run_test_cases=False):
        self.solution_program = CppProgram(solution_program, "compiled_solution_program")
        self.program_to_test = CppProgram(program_to_test, "compiled_program_to_test")
        self.solution_program_arg = solution_program_arg
        self.program_to_test_arg = program_to_test_arg
        self.test_runner = TestRunner()
        self.run_test_cases = run_test_cases

    def compile_and_run(self):
        self.solution_program.compile()
        self.program_to_test.compile()

        if self.run_test_cases:
            test_cases = ["5"]  # Modify this list based on your test cases
            self.solution_program_arg = ' '.join(test_cases)
            self.program_to_test_arg = ' '.join(test_cases)

        result_solution = self.solution_program.run([self.solution_program_arg] if self.solution_program_arg else [])
        result_to_test = self.program_to_test.run([self.program_to_test_arg] if self.program_to_test_arg else [])

        if self.run_test_cases:
            for case in test_cases:
                self.test_runner.run_test_case(self.solution_program, self.program_to_test, case)

        return result_to_test, result_solution

    def compare_results(self, result_to_test, result_solution):
        return result_to_test == result_solution

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python dart.py <path_to_solution_program> <path_to_program_to_test> [solution_program_arg] [program_to_test_arg] [-t]")
        sys.exit(1)

    solution_program = sys.argv[1]
    program_to_test = sys.argv[2]
    solution_program_arg = sys.argv[3] if len(sys.argv) >= 4 else None
    program_to_test_arg = sys.argv[4] if len(sys.argv) >= 5 else None
    run_test_cases = '-t' in sys.argv

    grader = CppGrader(solution_program, program_to_test, solution_program_arg, program_to_test_arg, run_test_cases)
    result_to_test, result_solution = grader.compile_and_run()

    if grader.compare_results(result_to_test, result_solution):
        print("Program passed the test.")
    else:
        print("Program failed the test.")
        print("Result from program to test:")
        print(result_to_test)
        print("Expected result from solution program:")
        print(result_solution)

    test_results = grader.test_runner.get_test_results()
    print("Test Results:", test_results)
