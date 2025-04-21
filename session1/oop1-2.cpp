#include <iostream>

class Benz {
public:
    bool startEngine() {
        // بررسی شروع سرویس‌های الکترونیکی و سیستم روشنایی
        if (startElectronicServices() && startLightSystem()) {
            std::cout << "Engine started successfully." << std::endl;
            return true;
        } else {
            std::cout << "Engine failed." << std::endl;
            return false;
        }
    }

private:
    // شروع سرویس‌های الکترونیکی ماشین
    bool startElectronicServices() {
        bool success = true;  // فرضی: همیشه سرویس الکترونیکی شروع می‌شود
        if (!success) {
            std::cout << "Failed to start Electronic Service." << std::endl;
            return false;  // اگر به هر دلیلی سرویس الکترونیکی نتونه شروع بشه
        }
        std::cout << "Electronic Service started." << std::endl;
        return true;
    }

    // شروع سیستم روشنایی ماشین
    bool startLightSystem() {
        bool success = true;  // فرضی: همیشه سیستم روشنایی شروع می‌شود
        if (!success) {
            std::cout << "Failed to start Light System." << std::endl;
            return false;  // اگر به هر دلیلی سیستم روشنایی نتونه شروع بشه
        }
        std::cout << "Light System started." << std::endl;
        return true;
    }
};

int main() {
    Benz b;
    
    // تلاش برای شروع موتور
    bool r = b.startEngine();
    
    // نمایش نتیجه‌ی تلاش برای شروع موتور
    if (r) {
        std::cout << "Engine started successfully in main." << std::endl;
    } else {
        std::cout << "Engine failed in main." << std::endl;
    }

    return 0;
}

