#include <queue>
#include <chrono>

using namespace std::chrono;


class FpsCounter {
private:
    std::queue<time_point<steady_clock>> m_Samples;
    milliseconds m_SamplingPeriod;
public:
    FpsCounter(milliseconds samplingPeriod = milliseconds(1000)) 
        : m_SamplingPeriod(samplingPeriod) {}


    void mark_frame() {
        m_Samples.push(steady_clock::now());
        cull_old_frames();
    }
    
    void reset() {
        while(!m_Samples.empty()) {
            m_Samples.pop();
        }
    }

    float get_fps() const {
        // We need at least two frames to calculate a delta
        if (m_Samples.size() < 2) return 0.0;

        // Calculate the total duration between the first and last sample in the queue
        auto duration = duration_cast<microseconds>(m_Samples.back() - m_Samples.front());
        if (duration.count() == 0) return 0.0;

        // The number of intervals is samples - 1
        // FPS = (count - 1) / total_time_in_seconds
        float seconds = duration.count() / 1000000.0f;
        return static_cast<float>(m_Samples.size() - 1) / seconds;

    }
private:
    void cull_old_frames() {
        if(m_Samples.empty()) return;

        while (m_Samples.back() - m_Samples.front() > m_SamplingPeriod) {
            m_Samples.pop();
        }
    }
};