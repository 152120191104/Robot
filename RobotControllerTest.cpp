#include "FestoRobotAPI.h"
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