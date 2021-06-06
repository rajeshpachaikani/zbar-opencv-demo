from pyzbar.pyzbar import decode
import cv2
import numpy as np

cap = cv2.VideoCapture(0)


def get_qr_data(input_frame):
    try:
        return decode(input_frame)
    except:
        return []


def draw_polygon(f_in, qro):
    if len(qro) == 0:
        return f_in
    else:
        for obj in qro:
            text = obj.data.decode('utf-8')
            pts = np.array([obj.polygon], np.int32)
            # print("Before Reshape::", pts.shape)
            pts = pts.reshape((4, 1, 2))
            # print("After Reshape::",pts.shape)
            cv2.polylines(f_in, [pts], True, (255, 100, 5), 2)
            cv2.putText(f_in, text, (50, 50), cv2.FONT_HERSHEY_PLAIN,1.5,(255,100,5),2)
        return f_in


while True:
    _, frame = cap.read()
    qr_obj = get_qr_data(frame)
    frame = draw_polygon(frame, qr_obj)
    cv2.imshow("DD", frame)
    # cv2.imshow("DD2", frame2)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

