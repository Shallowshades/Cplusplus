#include <bits/stdc++.h>

using namespace std;

class Observer;
class ConcreteObserver;
class Subject;
class WeatherData;

/// @brief 抽象观察者类
class Observer {
public:
    virtual ~Observer() {};
    virtual void Update(float temperature, float humidity, float pressure) = 0;
};

/// @brief 具体观察者类
class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const std::string& name) : m_name(name) {}
    virtual void Update(float temperature, float humidity, float pressure) override {
        std::cout << m_name << " received the update. Temperature: " << temperature << " Humidity: " << humidity << " Pressure: " << pressure << std::endl;
    }

private:
    string m_name;
};

/// @brief 抽象发布者类
class Subject {
public:
    Subject() = default;
    virtual ~Subject() {}
    virtual void RegisterObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void RemoveObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void NotifyObservers() = 0;
};

/// @brief 天气发布者类
class WeatherData : public Subject {
public:
    WeatherData() = default;

    void RegisterObserver(std::shared_ptr<Observer> observer) override {
        m_observers.push_back(observer);
    }
    void RemoveObserver(std::shared_ptr<Observer> observer) override {
        m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer));
    }
    void NotifyObservers() override {
        for (const auto& observer : m_observers) {
            observer->Update(m_temperature, m_humidity, m_pressure);
        }
    }
    void SetMeasurements(float temperature, float humidity, float pressure) {
        m_temperature = temperature;
        m_humidity = humidity;
        m_pressure = pressure;
        MeasurementChanged();
    }

private:
    void MeasurementChanged() {
        NotifyObservers();
    }

private:
    std::vector<std::shared_ptr<Observer>> m_observers;
    float m_temperature;
    float m_humidity;
    float m_pressure;
};

int main() {
    // 观察者
    auto observer1 = std::make_shared<ConcreteObserver>("Observer1");
    auto observer2 = std::make_shared<ConcreteObserver>("Observer2");
    auto observer3 = std::make_shared<ConcreteObserver>("Observer3");
    // 发布者 订阅
    auto weatherData = std::make_shared<WeatherData>();
    weatherData->RegisterObserver(observer1);
    weatherData->RegisterObserver(observer2);
    weatherData->RegisterObserver(observer3);
    // 事件变动
    weatherData->SetMeasurements(25.5f, 75.3f, 1013.2f);
    // 移除订阅者
    weatherData->RemoveObserver(observer1);
    // 事件变动
    weatherData->SetMeasurements(24.8f, 70.2f, 1012.1f);
    return 0;
}
