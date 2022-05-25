 case Custom:
					  LCDcommand(Clear);
            LCDstring("Cooking time?");
            delayms(1000);
						for (int i = 0; i < 5 ; i++)
            {
                s[i]='0';
							
            }
						s[2] = ':';
						LCDpos(1,0);
						LCDstring(s);
							
						while(1){
							key = getchar();
								if (key != 0)
										{
											if (s[0] == '0' && s[1] == '0' && s[2] == ':' && s[3] == '0' && s[4] == '0')
												{ 
														while(key == 0){key = getchar();}
														LCDcommand(Clear);
														LCDpos(0,0);
														LCDstring("Cooking time?");
														LCDpos(1,4);
														s[4] = key;
														LCDdata(s[4]);
														LCDpos(1,3);
														LCDdata(s[3]);
														LCDpos(1,2);
														LCDdata(s[2]);
														LCDpos(1,1);
														LCDdata(s[1]);
														LCDpos(1,0);
														LCDdata(s[0]);
														
														delayms(500);
												}
												else if(s[0] == '0' && s[1] == '0' && s[2] == ':' && s[3] == '0' && s[4] != '0')
												{
														while(key == 0){key = getchar();}
														LCDpos(0,0);
														LCDstring("Cooking time?");
														s[3] = s[4];
														LCDpos(1,4);
														s[4] = key;
														LCDdata(s[4]);
														LCDpos(1,3);
														LCDdata(s[3]);
														delayms(500);
												}
												else if(s[0] == '0' && s[1] == '0' && s[2] == ':' && s[3] != '0' && s[4] != '0')
												{
														while(key == 0){key = getchar();}
														LCDpos(0,0);
														LCDstring("Cooking time?");
														 
														s[1] = s[3];
														s[3] = s[4];
														LCDpos(1,4);
														s[4] = key;
														LCDdata(s[4]);
														LCDpos(1,3);
														LCDdata(s[3]);
														LCDpos(1,2);
														LCDdata(s[2]);
														LCDpos(1,1);
														LCDdata(s[1]);
														delayms(500);
												}
												else if (s[0] == '0' && s[1] != '0' && s[2] == ':' && s[3] != '0' && s[4] != '0')
												{
														while(key == 0){key = getchar();}
														LCDpos(0,0);
														LCDstring("Cooking time?");
														s[0] = s[1];
														s[1]= s[3];
														s[3] = s[4];
														LCDpos(1,4);
														s[4] = key;
														LCDdata(s[4]);
														LCDpos(1,3);
														LCDdata(s[3]);
														LCDpos(1,2);
														LCDdata(s[2]);
														LCDpos(1,1);
														LCDdata(s[1]);
														LCDpos(1,0);
														LCDdata(s[0]);
														
														delayms(500);
												}
												 
												else if (s[0] != '0' && s[1] != '0' && s[2] == ':' && s[3] != '0' && s[4] != '0'){
														currentState = Custom;
														break;
														 
													}
												}

											}