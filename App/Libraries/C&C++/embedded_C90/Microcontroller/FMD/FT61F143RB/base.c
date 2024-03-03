void DisableGlobalI()
{
	while(GIE)
	{
		GIE = 0;
		NOP();               
		NOP();            
	}
}