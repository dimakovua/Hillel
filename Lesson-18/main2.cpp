#include <atomic>
#include <mutex>

std::mutex m;
class mutex {
public:
	void lock() {
		bool expected = false;
		while(!_locked.compare_exchange_weak(expected, true, std::memory_order_acquire)) {
			expected = false;
		}
	}
 
	void unlock() {
		_locked.store(false, std::memory_order_release);
	}
 
private:
	std::atomic<bool> _locked;
};