# color
WHITE = "white"
RED = "red"
GREEN = "green"
YELLOW = "yellow"
MAGENTA = "magenta"
CYAN = "cyan"
COLOR_DICT = {"white": "\033[37m",
              "red": "\033[31m",
              "green": "\033[32m",
              "yellow": "\033[33m",
              "magenta": "\033[35m",
              "cyan": "\033[36m",
              "end": "\033[0m"}

# ----------------------------------------------------------

def print_color_str(color=WHITE, text=""):
    print(COLOR_DICT[color] + text + COLOR_DICT["end"])


def print_color_str_no_lf(color=WHITE, text=""):
    print(COLOR_DICT[color] + text + COLOR_DICT["end"], end="")
