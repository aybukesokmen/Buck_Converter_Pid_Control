# Buck_Converter_Pid_Control
/*
 * README.c
 *
 * Proje: Buck Converter – Kapalı Çevrim Gömülü Kontrol Sistemi
 * Yazar: Aybüke Sökmen
 * Tarih: Mayıs 2025
 *
 * Açıklama:
 * Bu gömülü sistem, değişken giriş voltajına ve yük koşullarına rağmen
 * sabit çıkış voltajı sağlayabilen kapalı çevrim bir Buck (indirgeyici)
 * DC-DC dönüştürücü kontrol yazılımıdır.
 * 
 * Sistem STM32F303RET6 mikrodenetleyicisi ile geliştirilmiştir ve aşağıdaki
 * temel görevleri yerine getirir:
 *
 * 1. Sensör Ölçümleri:
 *    - ADC üzerinden çıkış voltajı, çıkış akımı ve sıcaklık ölçümleri yapılır.
 *    - Bu veriler fiziksel birimlere çevrilir (sensor_converter.c).
 *
 * 2. PID Kontrol:
 *    - PID algoritması ile çıkış voltajı regülasyonu sağlanır.
 *    - PWM duty değeri PID_Update() fonksiyonu ile hesaplanır.
 *    - PID parametreleri dışarıdan CAN mesajı ile güncellenebilir.
 *
 * 3. PWM Sürücü:
 *    - TIM1 modülü üzerinden 20kHz frekansında PWM sinyali üretilir.
 *    - Duty değeri %0–%95 aralığında sınırlıdır.
 *
 * 4. Sistem Durum Makinesi (deviceloop.c):
 *    - INIT → MODE_EN → CONTROL → RUN → FAULT durumları arasında geçiş yapılır.
 *    - FAULT durumunda PWM sıfırlanır ve hata LED’i aktif edilir.
 *
 * 5. CAN Haberleşme:
 *    - Telemetri verileri her 100ms'de bir CAN üzerinden gönderilir.
 *    - Gönderilen bilgiler: Vout (mV), Iout (mA), Sıcaklık (°C), Durum bilgisi
 *    - CAN ID: 0x555, DLC: 8 byte
 *
 * 6. ISR:
 *    - TIM3_IRQHandler içinde periyodik PID kontrol uygulanabilir.
 *    - USB_LP_CAN_RX0_IRQHandler fonksiyonu ile gelen CAN mesajları alınır.
 *
 * Kullanılan Kaynak Dosyalar:
 * - control_pid_regulator.c: PID algoritması
 * - deviceloop.c: Ana durum makinesi ve kontrol akışı
 * - sensor_converter.c: ADC verilerinin dönüşümü
 * - protocol.c: CAN mesajlarının hazırlanması
 * - can_transmitter.c / can_receiver.c: CAN donanım sürücüleri
 * - saykal_io.c: GPIO üzerinden LED’ler ve buton okuma
 * - f303_Init.c: Donanım başlangıç ayarları (ADC, TIM, GPIO, vb.)
 *
 */
