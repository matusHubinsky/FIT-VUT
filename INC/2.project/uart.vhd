-- Project  : INC 
-- Author  	: Matus Hubinsky
-- xlogin	: xhubin04

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

-------------------------------------------------
entity UART_RX is
port(	
    CLK: 	    in std_logic;
	RST: 	    in std_logic;
	DIN: 	    in std_logic;
	DOUT: 	    out std_logic_vector(7 downto 0) := "00000000";
	DOUT_VLD: 	out std_logic := '0'
);
end UART_RX;  

-------------------------------------------------
architecture behavioral of UART_RX is
	signal cnt_s 		: std_logic_vector(4 downto 0) := "00000";
	signal cnt_b 		: std_logic_vector(2 downto 0) := "000";
	signal cnt_c 		: std_logic_vector(3 downto 0) := "0000";
	signal read_val 	: std_logic := '0';
	signal dout_val 	: std_logic := '0';
	signal cnt_rst  	: std_logic := '0';
	signal cnt_rst_s	: std_logic := '0';

begin
	-- FSM
    FSM: entity work.UART_FSM(behavioral)
    port map (
        CLK 	    => clk,
        RST 	    => rst,
        DIN 	    => din,
        CNT_B  		=> cnt_b,
        CNT_C  		=> cnt_c,
        CNT_S	    => cnt_s,
    	READ_VAL    => read_val,
    	DOUT_VAL 	=> dout_val,
    	CNT_RST  	=> cnt_rst,
    	CNT_RST_S  	=> cnt_rst_s
    );

	-- start counter Q[4:0]
    cnt_start: process(CLK, RST, CNT_RST_S, CNT_C)
    begin    
        if (RST = '1' or CNT_RST_S = '1') then
            CNT_S <= "00000";
        elsif (rising_edge(CLK)) then
            if(CNT_S < "11001")then
                CNT_S <= CNT_S + 1;
            end if;
        end if;
    end process;

	-- bit counter Q[2:0]
	cnt_byte: process(CLK, RST, CNT_RST, CNT_C)
	begin    
	    if (RST = '1' or CNT_RST = '1') then
			CNT_B <= "000";
		elsif (rising_edge(CLK) and CNT_C = "1111") then
			CNT_B <= CNT_B + 1;
		end if;
	end process;

	-- clock counter Q[3:0]
	cnt_clock: process(CLK, CNT_RST, RST)
	begin    
	    if (RST = '1' or CNT_RST = '1') then
			CNT_C <= "0000";
		elsif (rising_edge(CLK)) then
			CNT_C <= CNT_C + 1;
		end if;
	end process;

	-- demultiplexer + registers Q[7:0]
	demul: process(CNT_B, READ_VAL, DIN, CLK, RST)
	begin
		if (RST = '1') then
			DOUT <= "00000000";
		else 
			if (rising_edge(CLK) and READ_VAL = '1') then			
				case CNT_B is
					when "000" => DOUT(0) <= DIN; 
					when "001" => DOUT(1) <= DIN;
					when "010" => DOUT(2) <= DIN;
					when "011" => DOUT(3) <= DIN;
					when "100" => DOUT(4) <= DIN;
					when "101" => DOUT(5) <= DIN;
					when "110" => DOUT(6) <= DIN;
					when "111" => DOUT(7) <= DIN;
					when others => DOUT(7) <= DIN;
				end case;
			end if;
		end if;
	end process; 

	-- data valid
	valid: process(CLK, DOUT_VAL)
	begin
		if (rising_edge(CLK)) then
      		DOUT_VLD <= DOUT_VAL;
      	end if;
	end process;

end behavioral;