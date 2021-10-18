file_name = "scanner-test-output.txt"

test_number = 1
basic_test_inputs = ["+", "*", "/", "//", "=", "==", ")", "(", ":", "..", ",", "#",
                "<", "<=", ">", ">=", "~=", "a", "A", "z", "Z", "_", "_cf", "_FDF",
                "g80", "_c6f", "_0IF", "0", "9", "12", "02", "20.15", "11e+2", "11e2",
                "32e-1", "485e4", "20.15e3", "20.15e-3", "20.15e+3", "", "ahoj", "\"",
                "\t", "\n", "\\", "\\000", "\\255", "\\112"]
basic_test_outputs = ["+", "*", "/", "//", "=", "==", ")", "(", ":", "..", ",", "#",
                "<", "<=", ">", ">=", "~=", "a", "A", "z", "Z", "_", "_cf", "_FDF",
                "g80", "_c6f", "_0IF", "0", "9", "12", "02", "20.15", "11e+2", "11e2",
                "32e-1", "485e4", "20.15e3", "20.15e-3", "20.15e+3", "", "ahoj", "\"",
                "\t", "\n", "\\", "\000", "\255", "\112"]


with open(file_name, "w") as f:
    f.write("========== Basic Tests ==========\n\n")
    for i in range(len(basic_test_inputs)):
        f.write(f"test c.{test_number}\ninput: {basic_test_inputs[i]}\nname: {basic_test_outputs[i]}\nvalue:\n\n")
        test_number += 1

