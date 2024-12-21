#include "Record.h"
#include <iostream>
#include <cassert>

void testRecord() {
    // Record nesnesini oluştur
    Record record("test_file.txt");

    // Dosyayı aç
    assert(record.openFile() == true);
    std::cout << "Dosya başarıyla açıldı.\n";

    // Dosyaya yazma işlemi
    std::string lineToWrite = "Bu bir test satırıdır.";
    assert(record.writeLine(lineToWrite) == true);
    std::cout << "Dosyaya yazıldı: " << lineToWrite << "\n";

    // Dosyayı kapat
    assert(record.closeFile() == true);
    std::cout << "Dosya başarıyla kapatıldı.\n";

    // Dosyayı tekrar aç
    assert(record.openFile() == true);
    std::cout << "Dosya tekrar başarıyla açıldı.\n";

    // Dosyadan okuma işlemi
    std::string lineRead = record.readLine();
    std::cout << "Dosyadan okunan: " << lineRead << "\n";

    // Dosyayı kapat
    assert(record.closeFile() == true);
    std::cout << "Dosya başarıyla kapatıldı.\n";

    // Dosyayı sil
    remove("test_file.txt");
    std::cout << "Test dosyası silindi.\n";
}

int main() {
    testRecord(); // Test fonksiyonunu çağır
    return 0;
}