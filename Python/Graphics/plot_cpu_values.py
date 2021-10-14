import argparse
import matplotlib.pyplot as plt

from statistics import median

"""Script to generate plots from text files. Expected input can be seen under files/. First column
    should usr, second sys, and third idle. The tool used to perform the measurements does
    not matter as long as the output looks the same."""


def read_values_from_file(file_name: str):
    """Function to extract the data from the file."""
    usr = []
    kernel = []
    idle = []
    with open(file_name) as file:
        lines = file.readlines()
        for line in lines:
            splitted = line.split(" ")
            # remove empty entries after splitting
            splitted = [split for split in splitted if len(split) > 0]
            usr_val = int(splitted[0].strip())
            sys_val = int(splitted[1].strip())
            idle_val = int(splitted[2].strip())
            # ignore entry if all values are 0
            if usr_val == 0 and sys_val == 0 and idle_val == 0:
                continue
            usr.append(usr_val)
            kernel.append(sys_val)
            idle.append(idle_val)

    if len(usr) != len(kernel) or len(usr) != len(idle) or len(kernel) != len(idle):
        print("Size should be equal!")
        exit(1)
    return {"sys": kernel, "idle": idle, "usr": usr}


def create_plot(plot_title: str, usr: list, kernel: list, idle: list):
    """Function to create the plot using matplotlib."""
    time = list(range(0, len(usr)))
    plt.plot([], [], color="blue", label="usr", linewidth=3)
    plt.plot([], [], color="red", label="sys", linewidth=3)
    plt.plot([], [], color="black", label="idle", linewidth=3)

    plt.stackplot(time, usr, kernel, idle, colors=["blue", "red", "black"])

    mean_usr = sum(usr) / len(usr)
    mean_sys = sum(kernel) / len(kernel)

    median_usr = median(usr)
    median_sys = median(kernel)

    # plt.plot(seconds, values)
    plt.title(args.title)
    plt.xlabel("Time (s)")
    plt.ylabel("CPU usage (%)")

    plt.text(
        len(time) / 2,
        mean_usr + mean_sys + 4,
        "mean (usr+sys)",
        fontsize=10,
        color="white",
    )
    plt.plot(
        len(time) / 2,
        mean_usr + mean_sys,
        marker="o",
        markersize=5,
        markeredgecolor="white",
        markerfacecolor="white",
    )

    plt.text(
        len(time) / 2,
        median_usr + median_sys - 4,
        "median (usr+sys)",
        fontsize=10,
        color="white",
    )
    plt.plot(
        len(time) / 2,
        median_usr + median_sys,
        marker="o",
        markersize=5,
        markeredgecolor="white",
        markerfacecolor="white",
    )

    plt.legend()
    plt.show()


if __name__ == "__main__":
    """Main entry point of the script."""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--file",
        "-f",
        help="File to parse and plot.",
        type=str,
        default="vmstat-out.txt",
    )

    parser.add_argument(
        "--title",
        "-t",
        help="Title of the plot.",
        type=str,
        default="Performance",
    )
    args = parser.parse_args()
    values = read_values_from_file(args.file)
    create_plot(args.title, values["usr"], values["sys"], values["idle"])
