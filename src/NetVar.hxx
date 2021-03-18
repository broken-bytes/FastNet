#pragma once
#include <type_traits>
#include <cstdint>

namespace fastnet {
	struct Vector2 {
		float X;
		float Y;
	};
	struct Vector3 {
		float X;
		float Y;
		float Z;
	};

	struct Vector4 {
		float X;
		float Y;
		float Z;
		float W;
	};

	class INetVar {
	public:
		virtual ~INetVar() = 0;
	};
	template<
		typename T,
		typename = typename std::enable_if_t<
		std::is_fundamental<T>::value ||
		std::is_same<T, Vector2>::value ||
		std::is_same<T, Vector3>::value
		>>
		class NetVar : public INetVar {
		public:
			NetVar() {}
			NetVar(T value) {
				_value = value;
			}
			auto Value(T value) ->void {

			}

			auto Value() -> T {
				return _value;
			}

			auto Type() {
				return typeid(T);
			}
		private:
			T _value;
	};
}
