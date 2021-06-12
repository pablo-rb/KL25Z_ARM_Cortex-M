/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */


int main(void)
{

	SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
		
	SIM_SCGC5 |= (SIM_SCGC5_TSI_MASK);
	
	TSI0_GENCS |= (TSI_GENCS_MODE(0)
					| TSI_GENCS_REFCHRG(4)
					| TSI_GENCS_DVOLT(0)
					| TSI_GENCS_EXTCHRG(7)
					| TSI_GENCS_PS(4)
					| TSI_GENCS_NSCN(11)
					| TSI_GENCS_STPE_MASK);
	
	PORTB_BASE_PTR->PCR[16];
	PORTB_BASE_PTR->PCR[17];
	PORTB_BASE_PTR->PCR[18] |= (1<<8);
	PORTB_BASE_PTR->PCR[19] |= (1<<8);

	PTB_BASE_PTR->PDOR = 1 << 18;
	PTB_BASE_PTR->PDOR = 1 << 19;
	PTB_BASE_PTR->PDDR |= (3<<18);
	
	// 7.1) Començar un escaneig del canal 9 del touch
	TSI0_BASE_PTR->GENCS |= (1 << 7);
	TSI0_BASE_PTR->DATA |= ((9 << 28) | (1 << 22));
	
	// 7.2) Esperar a què s'acabi aquest escaneig
	while (!(TSI0_BASE_PTR->GENCS & 0x00000004)) 
	{
		;
	}


	// 7.3) Guardar el temps que ha trigat en realitzar-se aquest escaneig inicial
	uint16_t initialScanTime, newScanTime;  // el new s'utilitza per l'apartat 8
	initialScanTime = TSI0_BASE_PTR->DATA & 0xFFFF;
	
	
	// 7.4) Esborrar el bit EOSF del registre GENCS
	TSI0_BASE_PTR->GENCS |= (1 << 2);
	
	
	for(;;)
	{
		// 8.1) Fer els passos 7.1 i 7.2
		TSI0_BASE_PTR->DATA |= ((9 << 28) | (1 << 22));

		
		while (!(TSI0_BASE_PTR->GENCS & 0x00000004)) 
		{
			;
		}
		
		// 8.2) Comprovar si el temps que s'ha trigat és major
		newScanTime = TSI0_BASE_PTR->DATA & 0xFFFF;
	
		
		if (newScanTime > (initialScanTime + 20))
		{
			PTB_BASE_PTR->PDOR = (0 << 19); // APAGUEM LLUM VERMELLA
			PTB_BASE_PTR->PDOR = (1 << 18); // LLUM VERDA
			
		}
		else
		{
			PTB_BASE_PTR->PDOR = (0 << 18); // APAGUEM LLUM VERDA
			PTB_BASE_PTR->PDOR = (1 << 19); // LLUM VERMELLA
		}
		
		// 8.3) Esborrar el bit EOSF del registre GENCS
		TSI0_BASE_PTR->GENCS |= (1 << 2);
		
	}
	
	return 0;
}
