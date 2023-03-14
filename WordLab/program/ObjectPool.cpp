class objectpool {
		map<string,void *> Map;
	public:
		void * get(string name) {
			return Map[name];
		}
		void set(string name,void * address) {
			Map[name] = address;
		}
		void remove(string name) {
			Map.erase(name);
		}
		void clear() {
			Map.clear();
		}
} ObjectPool;
