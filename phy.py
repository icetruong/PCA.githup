import cv2
import numpy as np
def image_to_vector(image_path):
    try:
        # Đọc ảnh vào dưới dạng ảnh xám
        image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
        if image is None:
            print("Không thể đọc được ảnh. Vui lòng kiểm tra lại đường dẫn.")
            return None
        # Resize ảnh thành kích thước MxN 
        resized_image = cv2.resize(image, (3, 3))
        # Chuyển ma trận 2D thành mảng 1D (vector)
        vector = resized_image.flatten()
        return vector
    except Exception as e:
        print("Đã xảy ra lỗi:", e)
        return None
# Đường dẫn tới ảnh
image_path = "./tue.jpg"
# Chuyển ảnh thành vector
vector_data = image_to_vector(image_path)
if vector_data is not None:
    # Hiển thị kích thước của vector
    print("Kích thước của vector:", vector_data.shape)
    print("Vector:", vector_data)
    # Lưu vector dữ liệu vào tệp tin .npy(kiểu tiệp này chỉ sữ dụng được trên Python )
    np.save("vector_data.npy", vector_data)
    print("Dữ liệu vector đã được lưu thành công vào tệp vector_data.npy.")
import csv
# Mở hoặc tạo một tệp CSV(loại tệp này có thể được sữ dụng trong cả 2 ngôn ngữ C và Python) để lưu dữ liệu
with open('data.csv', 'w') as csvfile:
    # Tạo một đối tượng ghi CSV
    csvwriter = csv.writer(csvfile)
    # Ghi vector_data vào tệp CSV
    csvwriter.writerow(vector_data)
