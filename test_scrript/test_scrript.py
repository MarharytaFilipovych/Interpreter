import subprocess

def run_echo(input_data):
    process = subprocess.Popen(
        ['C:\\Margo\\Interpreter\\Interpreter.exe'],
        stdin=subprocess.PIPE, 
         stdout=subprocess.PIPE, 
         stderr=subprocess.PIPE,
        text=True
    )
    
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()

def test_echo():
    tests = [
        {"input": (
            "1 + 2\n"
            "var a = 10\n"
            "a + 4\n"
            "var omega = min(3,4)*6\n"
            "var c = max(300, 100 * max(2,3))*200\n"
            "3*(8.3+9.2822992)-min(8,8.0000000000001)/2829\n"
            "max(a,c)\n"
            "var b = pow(a,3)\n"
            "c = b / 7.99898988\n"
            "c\n"
            "pow(a,c)\n"
            "pow(c,b)*min(a,b)/abs(-300)\n"
            "-3*(-9)+a\n"
            "var d = a\n"
            "exit\n"
        ),
        "expected_output": (
            ">Echo: 3\n"
            ">Echo: a = 10\n"
            ">Echo: 14\n"
            ">Echo: omega = 18\n"
            ">Echo: c = 60000\n"
            ">Echo: 52.7441\n"
            ">Echo: 60000\n"
            ">Echo: b = 1000\n"
            ">Echo: c = 125.016\n"
            ">Echo: 125.016\n"
            ">Echo: 1.03701e+125\n"
            ">Echo: inf\n"
            ">Echo: 37\n"
            ">Echo: d = 10\n>"
        )},
        { "input": (
            "==92k\n"
            "min(,)\n"
            "d=3\n"
            "min(0,)\n"
            "min3\n"
            "exit\n"

        ),
        "expected_output": (
            ">Invalid input!\n"
            ">Invalid input!\n"
            ">Invalid input!\n"
            ">Invalid input!\n"
            ">Invalid input!\n>"
        )}
    ]

    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]
        
        output, error = run_echo(input_data)
        
        if error:
            print(f"Test failed for input:\n{input_data}")
            print(f"Error:\n{error}")
        elif output != expected_output:
            print(f"Test failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print(f"Test passed for input:\n{input_data}")

if __name__ == "__main__":
    test_echo()
