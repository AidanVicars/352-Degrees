#pragma once

class VMT
{

public:
	VMT(uintptr_t** _class)
	{

		//Constructor doing constructor things
		base_class = _class;
		original_vmt = *base_class;

		//Iterate through the vtable and increment till it reaches the end
		while (original_vmt[function_count])
			function_count++;

		//Multiply the size of pointer by the count to get table size
		table_size = function_count * sizeof(uintptr_t);

		//Create a new VMT the size of the original one
		new_vmt = std::make_unique<uintptr_t[]>(function_count);

		//Copy all the function pointers into our new table
		memcpy(new_vmt.get(), original_vmt, table_size);

		//Dereference and replace the pointer to the old vtable with our new one
		*base_class = new_vmt.get();

	}

	VMT(uintptr_t* vmt)
	{

		//Constructor doing constructor things
		original_vmt = vmt;

		//Iterate through the vtable and increment till it reaches the end
		while (original_vmt[function_count])
			function_count++;

		//Multiply the size of pointer by the count to get table size
		table_size = function_count * sizeof(uintptr_t);

		//Create a new VMT the size of the original one
		new_vmt = std::make_unique<uintptr_t[]>(function_count);

		//Copy all the function pointers into our new table
		memcpy(new_vmt.get(), original_vmt, table_size);



	}

	~VMT()
	{

		*base_class = original_vmt;

	}

	template<typename T>
	T GetOriginal(uint32_t index)
	{
		//Get original function from old vmt
		return reinterpret_cast<T>(original_vmt[index]);
	}

	void Hook(uint32_t index, void* new_func)
	{

		//
		new_vmt[index] = (uintptr_t)new_func;

	}

	void Unhook(uint32_t index)
	{

		new_vmt[index] = original_vmt[index];

	}

private:
	uint64_t** base_class;
	int function_count;
	size_t table_size;
	uintptr_t* original_vmt;
	std::unique_ptr<std::uintptr_t[]> new_vmt;

};