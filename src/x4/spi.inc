extern ti.WaitShort
extern ti.WaitLong

extern pSpiRange
extern mpSpiRange
extern spiValid
extern pSpiValid
extern mpSpiValid
extern spiStatus
extern pSpiStatus
extern mpSpiStatus
extern spiData
extern pSpiData
extern mpSpiData

extern lcd
extern lcd.width
extern lcd.height
extern lcd.size

macro spi cmd, params&
	ld	a, cmd
	call	spiCmd
	match any, params
		iterate param, any
			ld	a, param
			call	spiParam
		end iterate
	end match
end macro
;   END DEFINES
;Jacobly's SPI stuff
	;;;;;Jacobly's stuff

extern spiParam
extern spiCmd
