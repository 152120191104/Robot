[16:12, 21.12.2024] Elyesa Kyk: #include "FestoRobotAPI.h"
#include "Point.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath> // nan kontrolü için

void testObjectDetectionWithSensors() {
    // Webots API'si üzerinden robot ile bağlantı kur
    FestoRobotAPI* api = new FestoRobotAPI();
    api->connect(); // Robotla bağlantıyı başlat

    // Robotu bir miktar ileri hareket ettir
    api->move(FORWARD);
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2 saniye bekle
    api->stop(); // Robotu durdur

    bool objectDetected = false; // Nesne tespit durumu

    // Sensör verilerini güncelle
    for (int i = 0; i < 9; ++i) {
        double range = api->getIRRange(i); // Tüm IR sensörlerinden mesafe al
        std::cout << "IR Sensör " << i << " Mesafesi: " << range << " meters" << std::endl;

        // Mesafe geçerli mi ve belirli bir eşik değerinin altındaysa, nesne var demektir
        if (!std::isnan(range) && range >= 0 && range < 0.3) { // Eşik değerini 0.3 metreye düşürdük
            objectDetected = true; // Nesne tespit edildi
            break; // Nesne tespit edildiğinde döngüden çık
        }
    }

    if (objectDetected) {
        std::cout << "Nesne tespit edildi!" << std::endl;

        // Robotun konumunu al
        double x, y, theta;
        api->getXYTh(x, y, theta); // Robotun konum bilgilerini alıyoruz.

        // Point nesnesini oluştur
        Point point(x, y);

        // Nesnenin konumunu ekrana yazdır
        std::cout << "Robotun Mevcut Konumu:\n";
        std::cout << "X: " << point.getX() << " meters\n";
        std::cout << "Y: " << point.getY() << " meters\n";
    }
    else {
        std::cout << "Nesne tespit edilmedi." << std::endl;
    }

    // Bağlantıyı sonlandır
    api->disconnect();
    delete api; // Bellek sızıntısını önlemek için api nesnesini sil
}

int main() {
    testObjectDetectionWithSensors(); // Test fonksiyonunu çağır
    return 0;
}
[16:59, 21.12.2024] Elyesa Kyk: #include "LidarSensor.h"
#include "FestoRobotAPI.h"
#include <iostream>
#include <cassert>
#include <cstdlib> // Rastgele veri oluşturmak için
#include <ctime>   // Zamanı almak için

void testLidarSensor() {
    // Lidar sensör sayısını belirleyin
    const int rangeNumber = 10; // Örnek olarak 10 sensör
    LidarSensor lidar(rangeNumber);

    // Rastgele mesafe verileri oluştur
    srand(static_cast<unsigned int>(time(0))); // Rastgele sayı üreteci için tohum
    for (int i = 0; i < rangeNumber; ++i) {
        double randomDistance = static_cast<double>(rand() % 1000) / 100.0; // 0.0 ile 10.0 arasında rastgele mesafe
        lidar.update(); // Lidar verilerini güncelle
    }

    // Test: getRange(i) fonksiyonu
    for (int i = 0; i < rangeNumber; ++i) {
…
[17:02, 21.12.2024] Elyesa Kyk: #include "FestoRobotAPI.h"
#include "RobotControler.h"
#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>

void testRobotControler() {
    // FestoRobotAPI nesnesini oluştur ve bağlan
    FestoRobotAPI* api = new FestoRobotAPI();
    RobotControler controller(api);

    // Robotu bağla
    assert(controller.connectRobot() == true);
    std::cout << "Robot başarıyla bağlandı.\n";

    // Robotun başlangıç konumunu al
    Pose initialPose = controller.getPose();
    std::cout << "Başlangıç Konumu: X: " << initialPose.getX() << ", Y: " << initialPose.getY() << ", Theta: " << initialPose.getTheta() << "\n";

    // Robotu ileri hareket ettir
    controller.moveForward();
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2 saniye ileri hareket
    controller.stop();

    // Robotun konumunu kontrol et
    Pose forwardPose = controller.getPose();
    std::cout << "İleri Hareket Sonrası Konum: X: " << forwardPose.getX() << ", Y: " << forwardPose.getY() << ", Theta: " << forwardPose.getTheta() << "\n";

    // Robotu sola döndür
    controller.turnLeft();
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 1 saniye döndür
    controller.stop();

    // Robotun konumunu kontrol et
    Pose leftTurnPose = controller.getPose();
    std::cout << "Sola Dönme Sonrası Konum: X: " << leftTurnPose.getX() << ", Y: " << leftTurnPose.getY() << ", Theta: " << leftTurnPose.getTheta() << "\n";

    // Robotu sağa döndür
    controller.turnRight();
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 1 saniye döndür
    controller.stop();

    // Robotun konumunu kontrol et
    Pose rightTurnPose = controller.getPose();
    std::cout << "Sağa Dönme Sonrası Konum: X: " << rightTurnPose.getX() << ", Y: " << rightTurnPose.getY() << ", Theta: " << rightTurnPose.getTheta() << "\n";

    // Robotu geriye hareket ettir
    controller.moveBackward();
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2 saniye geriye hareket
    controller.stop();

    // Robotun konumunu kontrol et
    Pose backwardPose = controller.getPose();
    std::cout << "Geri Hareket Sonrası Konum: X: " << backwardPose.getX() << ", Y: " << backwardPose.getY() << ", Theta: " << backwardPose.getTheta() << "\n";

    // Robotu yanlamasına sola hareket ettir
    controller.moveLeft();
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2 saniye sola hareket
    controller.stop();

    // Robotun konumunu kontrol et
    Pose moveLeftPose = controller.getPose();
    std::cout << "Sola Yanlamasına Hareket Sonrası Konum: X: " << moveLeftPose.getX() << ", Y: " << moveLeftPose.getY() << ", Theta: " << moveLeftPose.getTheta() << "\n";

    // Robotu yanlamasına sağa hareket ettir
    controller.moveRight();
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2 saniye sağa hareket
    controller.stop();

    // Robotun konumunu kontrol et
    Pose moveRightPose = controller.getPose();
    std::cout << "Sağa Yanlamasına Hareket Sonrası Konum: X: " << moveRightPose.getX() << ", Y: " << moveRightPose.getY() << ", Theta: " << moveRightPose.getTheta() << "\n";

    // Robotu durdur
    controller.stop();

    // Robotu bağlantısını kes
    assert(controller.disconnectRobot() == true);
    std::cout << "Robot bağlantısı kesildi.\n";

    delete api; // Bellek sızıntısını önlemek için api nesnesini sil
}

int main() {
    testRobotControler(); // Test
    return 0;
}