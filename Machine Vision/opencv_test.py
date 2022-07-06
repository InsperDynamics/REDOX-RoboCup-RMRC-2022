import cv2
resolution_horizontal = 1280
resolution_vertical = 720
  
# define a video capture object
cap = cv2.VideoCapture(1)
cap.set(cv2.CAP_PROP_FPS, 30)
  
while True:
    ret, img = cap.read()
    resized = cv2.resize(img, (resolution_horizontal, resolution_vertical))
    cv2.imshow('test', resized)
    keypressed = cv2.waitKey(1)
    if keypressed == ord('q'):
        break
  
# After the loop release the cap object
cap.release()
# Destroy all the windows
cv2.destroyAllWindows()