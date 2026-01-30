# Tetris trên STM32F429

## 1. Tổng quan dự án 
- **Tên project:** Tetris trên STM32F429
- **Mục tiêu:** Triển khai trò chơi Tetris chạy trên kit STM32F429I‑DISCO; tích hợp TouchGFX cho giao diện.

---

## 2. Thiết kế phần cứng 


## 3. Thiết kế phần mềm 
### Kiến trúc tổng quan
- HAL (STM32Cube) — truy cập phần cứng
- FreeRTOS — quản lý các task (GUI, game, audio, input)
- TouchGFX — UI + game logic (phần lớn logic Tetris nằm trong TouchGFX GUI)
- BSP drivers — ILI9341, STMPE811, SDRAM

### Module chính & vị trí
- Khởi tạo phần cứng & RTOS: `Core/Src/main.c` (tạo các task: `GUI_Task`, `Music_Task`, `SFX_Task`, `defaultTask`)
- TouchGFX app (UI + game): `TouchGFX/gui/src/...` — *game logic chính nằm tại* `TouchGFX/gui/src/screen1_screen/Screen1View.cpp` (class `Tetromino`, board, scoring)
- TouchGFX init/wrapper: `TouchGFX/App/app_touchgfx.c`
- Drivers: `Drivers/BSP/Components/ili9341/*`, `Drivers/BSP/Components/stmpe811/*`
- Build system / Makefiles: `gcc/Makefile`, `TouchGFX/simulator/gcc/Makefile`

### Luồng chạy chính 
- Khởi động: `main()` khởi tạo HAL, clock và các peripheral chính (SDRAM, LTDC, I2C3, SPI5, TIM).
- TouchGFX: khởi tạo trước RTOS (`TouchGFX/App/app_touchgfx.c`) — chuẩn bị framebuffer và driver.
- RTOS: tạo queues (`myQueue01Handle`, `audioQueueHandle`) và các task chính: `GUI_Task` (UI & render), `defaultTask` (hành chính), `SFX_Task`/`Music_Task` (audio).
- Luồng dữ liệu (chính): Input (touch/buttons) → event → Game logic (TouchGFX view `Screen1View.cpp`) → Render (framebuffer → DMA2D → LTDC) → Display. Audio: event → `audioQueueHandle` → TIM.

### Các task FreeRTOS
- `GUI_Task` — chạy TouchGFX loop: xử lý event UI, cập nhật view/presenter và điều phối render (framebuffer → DMA2D → LTDC). (`Core/Src/main.c`)

- `defaultTask` — **input scanner**: quét nút/joystick, debounce, xử lý repeat/delay và gửi sự kiện (ví dụ `'L','R','O','D','M'`) vào `myQueue01Handle`; vòng lặp chạy ~20 ms (`osDelay(20)`).

- `SFX_Task` — đọc `audioQueueHandle` và phát hiệu ứng âm thanh ngắn bằng TIM.

- `Music_Task` — phát giai điệu nền (stream nốt từ `tetrisMelody`); priority thấp để không ảnh hưởng frame rate.

### Phối hợp giữa các task

- Giao tiếp chính bằng queues: myQueue01Handle (game/input) và audioQueueHandle (âm thanh).
- Input → driver → TouchGFX tạo event → GUI_Task xử lý hoặc đẩy message vào myQueue01Handle.
---

## 4. Chạy dự án
- STM32CubeIDE (có sẵn project trong `STM32CubeIDE/`)

- Mở với STM32CubeIDE: import `STM32CubeIDE/STM32F429I‑DISCO Debug.launch` hoặc mở `.ioc` và generate code hoặc import project vào STM32CubeIDE.  

## 5. Danh sách thành viên 
- **Họ tên —  Đóng góp**: 
- **Lưu Thịnh Khang** - Thiết kế kiến trúc, phát triển logic game.
- **Bùi Mạnh Hưng** - Lắp đặt thiết bị, phát triển phần cứng, chức năng âm thanh. 
- **Phùng Công Hiếu**: Thiết kế giao diện, phát triển logic game.

---

 