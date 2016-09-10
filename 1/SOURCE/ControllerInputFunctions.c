// I couldn't find the appropriate function which deals with a specific port. This is just a variation of the maple_enum_type function, credit for that goes to whoever wrote it. Probably BlueCrab or Dan Potter.

maple_device_t * DolmexicaFetchCont(int WhichPortUsed, uint32 ThisWeirdFunctionStuff) {
        
        int WhichUnitUsed;
	maple_device_t *DevicePointer;

	for (WhichUnitUsed=0; WhichUnitUsed<MAPLE_UNIT_COUNT; WhichUnitUsed++) {
			DevicePointer = maple_enum_dev(WhichPortUsed, WhichUnitUsed);
			if (DevicePointer != NULL && DevicePointer->info.functions & ThisWeirdFunctionStuff) {
				return DevicePointer;

			}
		}

	return NULL;
}