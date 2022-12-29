#pragma once

class c_base_handle {
protected:
	unsigned long m_index;
public:
	c_base_handle() { m_index = INVALID_EHANDLE_INDEX; }
	c_base_handle(const c_base_handle& other) { m_index = other.m_index; }
	c_base_handle(unsigned long value) { m_index = value; }
	c_base_handle(int entry, int serial_num) { init(entry, serial_num); }

	ALWAYS_INLINE void init(int entry, int serial_num) { m_index = static_cast<unsigned long>(entry | (serial_num << NUM_SERIAL_NUM_SHIFT_BITS)); }
	ALWAYS_INLINE void term() { m_index = INVALID_EHANDLE_INDEX; }

	ALWAYS_INLINE bool is_valid() const { return m_index != INVALID_EHANDLE_INDEX; }

	ALWAYS_INLINE int get_entry_index() const { return is_valid() ? m_index & ENT_ENTRY_MASK : NUM_ENT_ENTRIES - 1; }

	ALWAYS_INLINE int get_serial_number() const { return m_index >> NUM_SERIAL_NUM_SHIFT_BITS; }

	ALWAYS_INLINE int to_int() const { return m_index; }

	ALWAYS_INLINE bool operator!=(const c_base_handle& other) const { return m_index != other.m_index; }

	ALWAYS_INLINE bool operator==(const c_base_handle& other) const { return m_index == other.m_index; }

	ALWAYS_INLINE bool operator==(i_handle_entity* entity) const { return get() == entity; };

	ALWAYS_INLINE bool operator!=(i_handle_entity* entity) const { return get() != entity; }

	ALWAYS_INLINE bool operator<(const c_base_handle& other) const { return m_index < other.m_index; }

	ALWAYS_INLINE bool operator<(i_handle_entity* entity) const { return m_index < (entity ? entity->get_handle().m_index : INVALID_EHANDLE_INDEX); }

	ALWAYS_INLINE c_base_handle& operator=(i_handle_entity* entity) { return set(entity); }

	ALWAYS_INLINE c_base_handle& set(i_handle_entity* entity) {
		if (entity) {
			*this = entity->get_handle();
		}
		else {
			m_index = INVALID_EHANDLE_INDEX;
		}

		return *this;
	}

	i_handle_entity* get() const;
};