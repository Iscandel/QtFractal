#pragma once

//Blocks all object signals for the living time of the object
template<class T> class SignalBlocker {
	T *blocked;
	bool previous;
public:
	SignalBlocker(T *blocked)
		: blocked(blocked),
		previous(blocked->blockSignals(true)) {}
	~SignalBlocker() { blocked->blockSignals(previous); }
	T *operator->() { return blocked; }
};

template<class T> inline SignalBlocker<T> whileBlocking(T *blocked) {
	return SignalBlocker<T>(blocked);
}