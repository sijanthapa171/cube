#include "StatsPanel.h"
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>

static double GetProcessMemoryUsageMB() {
    std::ifstream file("/proc/self/status");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            std::string temp;
            int mem_kb;
            std::stringstream ss(line);
            ss >> temp >> mem_kb;
            return (double)mem_kb / 1024.0;
        }
    }
    return 0.0;
}

static double GetCPUUsage() {
    static unsigned long long lastTotalUser = 0, lastTotalUserLow = 0, lastTotalSys = 0, lastTotalIdle = 0;
    
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string cpuLabel;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    
    user = nice = system = idle = iowait = irq = softirq = steal = guest = guest_nice = 0;
    ss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

    unsigned long long totalUser = user - guest;
    unsigned long long totalUserLow = nice - guest_nice;
    unsigned long long totalSys = system + irq + softirq;
    unsigned long long totalIdle = idle + iowait;

    unsigned long long total = totalUser + totalUserLow + totalSys + totalIdle;
    unsigned long long lastTotal = lastTotalUser + lastTotalUserLow + lastTotalSys + lastTotalIdle;

    double percent = 0.0;
    if (total > lastTotal) {
        percent = (double)((totalUser + totalUserLow + totalSys) - (lastTotalUser + lastTotalUserLow + lastTotalSys)) / (total - lastTotal) * 100.0;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return percent;
}

void DrawStatsPanel(float cameraRadius, Vector2 cameraAngle) {
    int sw       = GetScreenWidth();
    int panelW   = 230;
    int panelH   = 140;
    int panelX   = sw - panelW - 10;
    int panelY   = 10;
    int fps      = GetFPS();
    DrawRectangle(panelX, panelY, panelW, panelH, { 0, 0, 0, 160 });
    DrawRectangleLines(panelX, panelY, panelW, panelH, { 80, 80, 100, 200 });

    Color fpsColor = (fps >= 55) ? (Color){ 80, 220,  80, 255 }
                   : (fps >= 30) ? (Color){ 220, 180, 60, 255 }
                                 : (Color){ 220,  60, 60, 255 };
    DrawText(TextFormat("FPS: %d", fps),
             panelX + 10, panelY + 10, 18, fpsColor);

    Color statColor = { 180, 200, 255, 255 };
    DrawText(TextFormat("Zoom:  %.1f",  cameraRadius),
             panelX + 10, panelY + 34, 15, statColor);
    DrawText(TextFormat("Yaw:   %.1f deg", cameraAngle.x * (180.0f / PI)),
             panelX + 10, panelY + 56, 15, statColor);
    DrawText(TextFormat("Pitch: %.1f deg", cameraAngle.y * (180.0f / PI)),
             panelX + 10, panelY + 78, 15, statColor);
             
    double memUsage = GetProcessMemoryUsageMB();
    double cpuUsage = GetCPUUsage();
    
    DrawText(TextFormat("Memory:   %.1f MB", memUsage),
             panelX + 10, panelY + 100, 15, statColor);
}
