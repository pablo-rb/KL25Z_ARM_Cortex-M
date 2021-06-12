/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

uint16_t baseScanTime = 6;

void TSI0_IRQHandler() __attribute__ ((interrupt("IRQ")));

void TSI0_IRQHandler (void) {

		// Guardar el temps que ha trigat en realitzar-se aquest escaneig inicial
		uint16_t newScanTime;
		newScanTime = TSI0_BASE_PTR->DATA & 0xFFFF;

		uint16_t diffScanTime = newScanTime - baseScanTime;
		
		if (diffScanTime > 3)
		{
			PTB_BASE_PTR->PDOR = (0 << 19); //APAGUEM LLUM VERMELLA
			PTB_BASE_PTR->PDOR = (1 << 18); // LLUM VERDA
		}
		else
		{
			PTB_BASE_PTR->PDOR = (0 << 18); // APAGUEM LLUM VERDA
			PTB_BASE_PTR->PDOR = (1 << 19); // LLUM VERMELLA
		}	
		
		// Esborrar el bit EOSF del registre GENCS
		TSI0_BASE_PTR->GENCS |= (1 << 2);
		
		// Començar un escaneig del canal 9 del touch
		TSI0_BASE_PTR->DATA |= ((9 << 28) | (1 << 22));
}

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
		
		// Començar un escaneig del canal 9 del touch
		TSI0_BASE_PTR->GENCS |= (1 << 7);
		TSI0_BASE_PTR->DATA |= ((9 << 28) | (1 << 22));
	
		
		// Esperar a què s'acabi aquest escaneig
		while (!(TSI0_BASE_PTR->GENCS & 0x00000004)); 
		
		// Activacio bit 6 (IRQ Touch)
		TSI0_BASE_PTR->GENCS |= (1 << 6);
		
		baseScanTime = TSI0_BASE_PTR->DATA & 0xFFFF;
		
		// Esborrar el bit EOSF del registre GENCS
		TSI0_BASE_PTR->GENCS |= (1 << 2);

		
		// Activar IRQ Global
		NVIC_BASE_PTR->ICPR |= (1 << 26); // borrem estat pendent
		NVIC_BASE_PTR->ISER |= (1 << 26); // acceptacio IRQ
	
		TSI0_BASE_PTR->DATA |= ((9 << 28) | (1 << 22));
		
	    	while(1)
	    	{
	    		asm("WFI");
	    	}

	return 0;
}
