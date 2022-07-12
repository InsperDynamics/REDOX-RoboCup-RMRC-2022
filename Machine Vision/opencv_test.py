import cv2
resolution_horizontal = 800
resolution_vertical = 450
  
# define a video capture object
cap = cv2.VideoCapture(1)
cap.set(cv2.CAP_PROP_FPS, 30)
cap.set(cv2.CAP_PROP_CONVERT_RGB, False)
  
while True:
    ret, img = cap.read()
    #resized = cv2.resize(img, (resolution_horizontal, resolution_vertical))
    print(cap.get(cv2.CAP_PROP_FRAME_WIDTH), cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    cv2.imshow('test', img)
    keypressed = cv2.waitKey(1)
    if keypressed == ord('q'):
        break
  
# After the loop release the cap object
cap.release()
# Destroy all the windows
cv2.destroyAllWindows()