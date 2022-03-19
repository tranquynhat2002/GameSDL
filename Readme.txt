I. HƯỚNG DẪN CÀI ĐẶT SDL2.0 VÀO VISUAL STUDIO 2012 để chạy game 

B1: Mở file GameDemoSDL
B2: Trên màn hình visual, bấm chuột phải vào project, chọn properties -> VC++ Directies -> Include Directiories rồi chọn add để paste các dòng sau:
$(SolutionDir)LibSdl2\SDL2_ttf-2.0.14\include
$(SolutionDir)LibSdl2\SDL2_mixer-2.0.2\include
$(SolutionDir)LibSdl2\SDL2_image-2.0.3\include
$(SolutionDir)LibSdl2\SDL2-2.0.8\include
B3: Chọn Library Directories rồi paste các dòng sau
$(SolutionDir)LibSdl2\SDL2-2.0.8\lib\x86
$(SolutionDir)LibSdl2\SDL2_mixer-2.0.2\lib\x86
$(SolutionDir)LibSdl2\SDL2_image-2.0.3\lib\x86
$(SolutionDir)LibSdl2\SDL2_ttf-2.0.14\lib\x86
B4: ở phần Linker chọn Input->Additional Dependencies rồi thêm các file lib sau:
SDL2.lib
SDL2main.lib
SDL2_image.lib
SDL2_mixer.lib
SDL2_ttf.lib
B5: Build thử. sau khi build thành công ấn Ctrl+F5 để chạy chương trình.

II. GIỚI THIỆU GAME VÀ CÁC CHỨC NĂNG CHÍNH CỦA GAME

Game được xây dựng dựa trên ý tưởng của game Contra cổ điển, có thay đổi nhân vât, đồ họa, các tính năng còn đơn giản

1)Nhiệm vụ: nhân vật sẽ phải vượt qua các chướng ngại vật, mối hiểm họa để đi đến đích. Trên đường đi, nhân vật có thể ăn các đồ hỗ trợ để tăng thêm điểm. 
Khi va chạm với các mối hiểm họa, nhân vật sẽ bị chết. Người chơi phải hoàn thành game trong thời gian quy định, nếu không trò chơi sẽ kết thúc

2)Đặc điểm của game:
Game có tính điểm, tính thời gian
Sau mỗi lần thua, có thể chơi lại, game sẽ được reset lại từ đầu
Game sử dụng hình ảnh, âm thanh, map tự tạo hoặc chỉnh sửa từ Internet
Các mối hiểm họa (gồm mối hiểm họa tĩnh và động, có thể di chuyển được) được sinh ra theo quy luật
Sử dụng SDL_image, SDL_Mixer, SDL_TTF

3)Các chức năng chính của game
CommonFunc: chứa các thuộc tính chung của game như kích cỡ màn hình game, màu sắc, khai báo các biến (màn hình, âm thanh), 
            định nghĩa kích thước của ô, số hàng, số cột; chứa các struct như Map (thể hiện trạng thái của các ô), 
            Input (dành cho di chuyển nhân vật), CheckCollision (chứa hàm xử lí va chạm)
BaseObject: chứa các hàm chuyên xử lí đối tượng hình ảnh, các đối tượng sau khi sử dụng hình ảnh đều kế thừa từ lớp này
MainObject: định nghĩa tốc độ nhảy, rơi và di chuyển của nhân vật, 
            chứa các hàm như hàm xử lí sự kiện, kiểm tra va chạm của nhân vật với map, làm cho nhân vật di chuyển, tạo hiệu ứng di chuyển cho nhân vật,...
ThreatsObject: chứa các hàm tương tự như MainObject nhưng quản lí các đối tượng liên quan đến các mối hiểm họa
game_map: chứa các lớp, các hàm quản lí việc xây dựng map, đọc các thông tin về map trong text, load hình ảnh và điền hình ảnh vào từng vị trí tương ứng
ImpTimer: quản lí thời gian và xử lí fps của game
TextObject: quản lí các đối tượng liên quan đến text (kích thước, màu sắc, nội dung)
BulletObject: quản lí về vấn đề đạn bắn trong game, tạo ra đạn và hướng đạn bắn
ExplosionObject: quản lí vấn đề vụ nổ khi va chạm trong game
Geometric: hàm dùng để vẽ hình 
main: là hàm gọi các hàm trên ra để chạy 
MenuGame: hàm chuyên xử lí các vấn đề ở menu và các chức năng trong menu
PlayerPower: hàm hiển thị hình ảnh như số mạng, số đồng tiền, thời gian và hiển thị chỉ số tương ứng bên cạnh



4) Giải thích 1 số phương pháp trong code

a) Cách xây dựng map, kỹ thuật tile-map
- Kỹ thuật tile-map là kỹ thuật mà người ta chia bản đồ game thành các ô vuông có kích cỡ bằng nhau. Mỗi ô vuông sẽ có 1 giá trị số để thể hiện trạng thái của
  ô
  Giả sử: 0 là chỉ số không chèn ảnh
          ô đất dưới cùng có chỉ số = 1
          thùng gỗ có chỉ số = 2
          đồng tiền = 3
  Các chỉ số của từng ô sẽ được lưu trong một file text có tên map.dat
  Bản đồ có bao nhiêu hàng bao nhiêu cột thì trong file map.dat cũng sẽ có từng đấy hàng và cột thể hiện trạng thái của từng ô
- Do đó ta chỉ cần làm các nhiệm vụ 
  + Đọc file map.dat và lưu trữ trạng thái của từng ô tile-map vào một mảng dữ liệu 
  + Load hình ảnh các dạng ô của map bản đồ theo từng trạng thái
  + Sau đó ta sẽ chèn hình ảnh các dạng ô của map load được vào bản đồ qua file map.dat rồi sau đố hiển thị map đã ghép được ra màn hình 

b) Load nhân vật và hiệu ứng animation cho nhân vật 
- Sử dụng frame_clip để lưu trữ lần lượt kích thước và vị trí của các frame trong 1 dãy hình ảnh nhân vật game và khi thực hiện show ảnh thì liên tục các frame này được  
  thay đổi luân phiên qua nhau từ frame đầu tiên cho đến frame cuối rồi quay lại tiếp tục từ frame đầu 
  Nó tạo nên hiệu ứng động về hình ảnh giống như nguyên lí 24 hình/s
- Các quái xuất hiện trong game sẽ được làm tương tự như nhân vật, chỉ khác ở chỗ nhân vật ta dùng bàn phím để di chuyển (tăng, giảm tọa độ) còn nhân vật ta sẽ dùng hàm 
for để tự tăng giảm tọa độ làm cho nhân vật tự di chuyển

c) Xử lí va chạm giữa nhân vật và bản đồ tile-map
- Nhân vật game khi xuất hiện trên bản đồ, thì nó sẽ có tọa độ vị trí tương ứng, ta gọi là X va Y
  Từ vị trí X và Y ta sẽ biết được nhân vật game đang đứng ở vị trí ô thứ bao nhiêu của tile-map
  Sau đó khi biết được vị trí ô của nhân vật game chúng ta sẽ kiểm tra xem tại ô đó, tile-map có trạng thái bằng bao nhiêu
  + Nếu ô tile-map = 0, nhân vật có thể di chuyển bình thường 
  + Nếu ô tile-map khác 0, có nghĩa đang tồn tại map thì nhân vật sẽ không vượt qua được và sẽ chỉ đứng yên tại ô tile-map trước đó 
- Ta sẽ phải xử lí 4 hướng trái, phải, trên, dưới để nhân vật đứng, di chuyển trên bản đồ, bị chặn khi va chạm với tile-map
- Ngoài ra riêng đồ hỗ trợ trong game (VD như đồng tiền), nếu gặp ta sẽ lưu lại giá trị tại ô đó về 0 để đồng tiền biến mất 
 
d) Di chuyển màn hình khi nhân vật di chuyển 
- Cơ chế của việc di chuyển màn hình là tính toán lại giá trị tọa độ điểm bắt đầu và kết thúc của map hiển thị ra màn hình dựa vào vị trí tọa độ của nhân vật X và Y
  Từ X và Y ta sẽ xác định được rằng nhân vật đã di chuyển đến gần cuối map chưa, nếu đến gần cuối map thì ta sẽ gán lại vị trí bắt đầu và kết thúc của map để hiển thị 
  ra màn hình

e) Xử lí va chạm trong game
- Ta có 3 va chạm cần xử lí
  + Va chạm giữa nhân vật và quái
  + Va chạm giữa đạn của nhân vật và quái
  + Va chạm giữa đạn của quái và nhân vật 
- Ta sẽ xác định được tọa độ của: nhân vật, quái và đạn 
  + Nếu tọa độ trùng nhau ta sẽ cho nổ và nhân vật sẽ xuất hiện lại 