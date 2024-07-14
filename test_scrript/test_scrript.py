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
            "var a = 10\n"
            "a + 4\n"
            "var omega = min(3,4)*6\n"
            "var c = max(300, 100 * max(2,3))*200\n"
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
            ">Echo: a = 10\n"
            ">Echo: 14\n"
            ">Echo: omega = 18\n"
            ">Echo: c = 60000\n"
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
        )},
        {"input": (
            "1 + 2\n"           
            "3*(8.3+9.2822992)-min(8,8.0000000000001)/2829\n" 
            "2345889900-(2*3+7/222222*(6789022222+2222222))\n"
            "14+89\n"
            "exit\n"
        ),
        "expected_output": (
            ">Echo: 3\n"
            ">Echo: 52.7441\n" 
            ">Echo: 2.34567e+09\n"
            ">Echo: 103\n>"
        )},
         {"input": (
            "var a = 12/0\n"           
            "var c = 12/a\n"   
            "c+a\n"
            "exit\n"
        ),
        "expected_output": (
            ">Echo: a = inf\n"
            ">Echo: c = 0\n"
            ">Echo: inf\n>"
        )},
         {"input": (
            "var comma = 45.897\n"           
            "var delta = 4.00045\n"   
            "var sab = -333.44432\n"
            "abs(sab)\n"
            "sab\n"
            "pow(comma, delta)\n"
            "pow(delta,comma)\n"
            "pow(delta,0.00000000032)\n"
            "exit\n"
        ),
        "expected_output": (
            ">Echo: comma = 45.897\n"
            ">Echo: delta = 4.00045\n"
            ">Echo: sab = -333.444\n"
            ">Echo: 333.444\n"
            ">Echo: -333.444\n"
            ">Echo: 4.44514e+06\n"
            ">Echo: 4.31509e+27\n"
            ">Echo: 1\n>"
        )},
         {"input": (
            "var cloud = min(8*9, -8)\n"           
            "var sun = abs(-9)+pow(7, 8) * max(8, min(7,1))\n"   
            "cloud = cloud * (100000)\n"
            "var sum = cloud + sun\n"
            "var house = sum - 1000000000\n"
            "var lion = house * 100\n"
            "lion = lion * (-1)\n"
            "exit\n"
        ),
        "expected_output": (
            ">Echo: cloud = -8\n"
            ">Echo: sun = 4.61184e+07\n"
            ">Echo: cloud = -800000\n"
            ">Echo: sum = 4.53184e+07\n"
            ">Echo: house = -1e+09\n"
            ">Echo: lion = -1e+11\n"
            ">Echo: lion = 1e+11\n>"
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
