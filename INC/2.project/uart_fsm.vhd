-- Project  : INC 
-- Author  	: Matus Hubinsky
-- xlogin	: xhubin04

library ieee;
use ieee.std_logic_1164.all;

-------------------------------------------------
entity UART_FSM is
port (
	-- inputs
	DIN 		: in std_logic;
   	CLK 		: in std_logic;
   	RST 		: in std_logic;
   	CNT_B 		: in std_logic_vector(2 downto 0);
   	CNT_S 		: in std_logic_vector(4 downto 0);
   	CNT_C 		: in std_logic_vector(3 downto 0);
	-- outputs
	READ_VAL	: out std_logic := '0';
	DOUT_VAL	: out std_logic := '0';
	CNT_RST		: out std_logic := '0';
	CNT_RST_S 	: out std_logic := '0'
);
end entity UART_FSM;

-------------------------------------------------
architecture behavioral of UART_FSM is

    type STATE_TYPE is (START_STATE, READ_STATE, END_STATE);
    
    signal curl_state : STATE_TYPE := START_STATE;
    signal prew_DIN : std_logic  := '0';
    
begin
	state_register: process(RST, CLK)
	begin
		if (rising_edge(CLK)) then
		    if(RST = '1')then 
			    curl_state <= START_STATE;
		    else
                case curl_state is
                    when START_STATE =>
                        DOUT_VAL <= '0';
                  		READ_VAL <= '0';
                        -- cakanie na start bit v FSM
                        if (prew_DIN = '1' and DIN = '0') then
                        	CNT_RST_S <= '1';
                        else 
                        	CNT_RST 	<= '0';
                        	CNT_RST_S 	<= '0';
                        end if;
                        if (CNT_S = "10011") then
                        	CNT_RST <= '1';
                        	curl_state <= READ_STATE;
                        end if;
                        
                    when READ_STATE =>
                    	CNT_RST <= '0';
                        if (CNT_C = "0001") then
                        	READ_VAL <= '1';
                       		DOUT_VAL <= '0';
                       		if (CNT_B = "111") then
                       			curl_state <= END_STATE;
                       		end if;
	                    else
                        	READ_VAL <= '0';
                        end if;
                        
                    when END_STATE =>
                            READ_VAL <= '0';
                        if (CNT_C = "0001") then
                            if(DIN = '1')then
                                DOUT_VAL <= '1';
                            end if;
                            curl_state <= START_STATE;
                        end if;
                        
                                                
                    when others =>
                        curl_state <= START_STATE;                
                end case;
                
                prew_DIN <= DIN;
                
		    end if;
		end if;
	end process;
	
end behavioral; 	