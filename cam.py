import cv2
from time import sleep
import time
from subprocess import call, check_output
import os
import glob


class CustomError(Exception):
    pass

def stream():
    open_camera()
    while True:
        take_picture()
        clear_computer_folder(folder='images/')
        transfer_image(from_path='/sdcard/DCIM/Camera/', to_path='images/')
        display_image()
        if cv2.waitKey(1) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            break

def open_camera():
    if call("adb shell am start -a android.media.action.IMAGE_CAPTURE", shell=True) == 1:
        raise CustomError("Error opening camera app")
    sleep(5)
    
def take_picture():
    if call("adb shell input keyevent CAMERA", shell=True) == 1:
        raise CustomError("Error taking picture")
    sleep(0.3) # give time for Android to process image taken
    
def clear_computer_folder(folder):
    files = glob.glob(os.path.join(folder, '*.jpg'))
    if len(files) != 0:
        os.remove(files[0])
    
def transfer_image(from_path, to_path):
    most_recent = check_output(f"adb shell ls -t {str(from_path)} | head -n 1", shell=True).decode().strip()
    if call(f"adb pull /sdcard/DCIM/Camera/{most_recent} {str(to_path)}" , shell=True) == 1:
        raise CustomError("Error transfering image from Android phone to computer")
    
def display_image():
    files = glob.glob('images/*.jpg')
    if len(files) == 0:
        return
    
    most_recent = files[0]
    img = cv2.imread(most_recent)
    if img is None:
        raise CustomError("Error displaying image on computer")

    cv2.imshow("Security Camera Feed", img)
    
    
if __name__ == "__main__":
    stream()