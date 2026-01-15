from random import randint

input_name   = "input"
expout_name  = "expected_output"
linhas       = 5

input_file  = open(input_name, "w")
expout_file = open(expout_name, "w")

input_file.write(f"{linhas}\n")

for _ in range(linhas):
    base     = randint(-5, 5)
    exponent = randint(1, 27)

    assert(-(2 ** 63) < base ** exponent < (2 ** 63 - 1))

    input_file.write(f"{base}^{exponent}\n")
    expout_file.write(f"{base ** exponent}\n")
