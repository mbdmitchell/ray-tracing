import sys

from PIL import Image


def view_ppm_image(image_path):
    try:
        img = Image.open(image_path)
        img.show()
    except IOError:
        print("Unable to load image")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python printPPM.py <image_path>")
    else:
        image_path = sys.argv[1]
        view_ppm_image(image_path)
