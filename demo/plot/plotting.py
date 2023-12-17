import numpy as np
import matplotlib.pyplot as plt


def gather_data(filename, data, skip_header_lines, min_key_size, max_key_size):
    num_points = max_key_size - min_key_size + 1
    with open(filename) as file:
        point_counter = 0
        section = 0
        for idx, line in enumerate(file):
            if idx < skip_header_lines:
                continue
            if point_counter == num_points:
                point_counter = 0
                section += 1
                continue
            point_counter += 1
            time, key_size = line.partition(" ")[::2]
            data[section][int(key_size)] = float(time)


def main() -> int:
    # ------------------- RSA -------------------
    encrypt = {}
    decrypt = {}
    keygen  = {}
    data = [encrypt, decrypt, keygen]

    gather_data("resources/rsa32.txt", data, 3, 3, 32)

    figure, axes = plt.subplots(3, figsize = (8, 10))
    figure.suptitle("RSA performance")

    axes[0].plot(list(keygen.keys())[5:], list(keygen.values())[5:])
    axes[0].set_title("Keygen")
    axes[0].set(ylabel = "time [ns]")

    axes[1].plot(list(encrypt.keys()), list(encrypt.values()))
    axes[1].set_title("Encrypion")
    axes[1].set(ylabel = "time [ns]")

    axes[2].plot(list(decrypt.keys()), list(decrypt.values()))
    axes[2].set_title("Decryption")
    axes[2].set(xlabel = "key size [bit]", ylabel = "time [ns]")

    plt.savefig("rsa.png")


if __name__ == '__main__':
    main()
