; ----------------------------------------------------------------------------
; viivanyhtalo.asm
; 10.03.2014, P. Heinonen
;
; Harjoitusty� K�skykieli 132C1 2013-2014 opintojakso, INTKAI10X2
;
; Win32 konsolisovellus Assembly-kielell� joka piirt��
; viivan X-merkeill� kun k�ytt�j� sy�tt�� 
; kulmakertoimen, vakiotermin ja x:n yl�rajan.
; T�m� kuvaa ensimm�ist� versiota jossa
; sallittu sy�tealue on rajattu v�lille: 0-9
; x:n alin arvo on 0 ja ylin arvo k�ytt�j�n antama 0-9
; Koordinaatiston akseleiden "piirt�misen" j�tin pois.
;
; Prosessori: 386 tai uudempi
; K��nt�j�: MASM/ML
; OS: Win32/Win64
;
; Sisennyksess� k�ytet��n sekoitusta Microsoftin coding conventionista
; ja Irvine32 assembly-kirjastosta. Labelointi ja macron ja proseduurien
; otsikkokommentointi on Irvine32 mukainen.
; Irvine32 kirjastosta saisi my�s v�rit mukaan konsolille. En ottanut
; k�ytt��n. Includella testasin v�rityst� ja hyvin toimi.
; 
; Komentorivilt� k��nn�s: "ml hello.asm /c"
; Komentorivilt� linkkaus: "link hello kernel32.lib mvcrt.lib 
; lis�optio jos haluaa _main sijasta k�ytt�� 
; omaa entrypointia: /subsystem:console /entry:letsGo"
; ----------------------------------------------------------------------------

		
		.586
		.model flat
		EXTERN _puts:near
		EXTERN _putchar:near
		EXTERN _getchar:near
		;public _letsGo			; t�ll� voi korvata _main-PROCin mik�li entry-asetetaan.
								; Koin paremmaksi k�ytt�� _main:ia sill� VS2012 debuggeri
								; ei n�ytt�nyt saavan breakpointeja toimimaan 
								; kustomoituun entrypointiin

		include macrot.inc		; makrot sy�tteiden k�sittelyyn
		



;-------------------------------------------------------------------------------------------------
;                      SHARED DATA                                                               -
;-------------------------------------------------------------------------------------------------

			.DATA
promptKulma	db						"Anna kulmakerroin (0-9):",0
promptVakio	db						"Anna vakiotermi (0-9):",0
promptUud	db						"Piirretaanko uudelleen (k/e)?",0
promptXlim	db						"Anna funktion x-termin ylaraja (0 on alaraja):",0
dashLine	db						13,10,13,10,"-------------------------------",13,10,0
oneSpace	dword					' ',0
dot			dword					' ',0
SPACE		equ						32d
CR			equ						13d
LF			equ						10d
varKulma	byte					0						
varVakio	byte					0						
varXLow		byte					0						
varXHigh	byte					0						
varY		byte					0						
counter		byte					0						
previousY	byte					0


			.stack	; ei v�ltt�m�t�n

;-------------------------------------------------------------------------------------------------
;                      PUBLIC PROCEDURES                                                         -
;-------------------------------------------------------------------------------------------------

			.CODE

;-------------------------------------------------------------------------------------------------
_main		PROC
;  
; P��ohjelma. Kutsuu aliohjelmia joilla kysyt��n k�ytt�j�n sy�tteit� 
; ja lasketaan Y:n arvot.
;-------------------------------------------------------------------------------------------------

L0:			Nollaa					eax						; nollataan eax rekisteri varmuuden 
															; vuoksi.
			call					AskVars					; luetaan k�ytt�j�n sy�tteet muuttujiin
			
			call					CalculateY				; piirret��n y:n kuvaaja
															; ei k�ytet� loop-operaattoria, 
															; koska joudutaan pilkkomaan 
															; koodiblokkeja turhaan - "long jump"-ongelma.
															; jossakin v�itettiin, ett� silmukka 
															; suoriutuu nopeammin ilman loop-operaatiota, 
															; tied� sitten, en vertaillut sen enemp��.
			call					AskAgain				; Kysyt��n piirret��nk� uudelleen		
			ret
_main		ENDP

;-------------------------------------------------------------------------------------------------
AskVars		PROC
;  
; Kysyy k�ytt�j�lt� sy�tteet ja asettaa ne muuttujiin
;-------------------------------------------------------------------------------------------------
			
L5:			ConsoleWriteString		promptKulma
			ConsoleReadNumE			varKulma, L5
L6:			ConsoleWriteString		promptVakio
			ConsoleReadNumE			varVakio, L6
L7:			ConsoleWriteString		promptXlim
			ConsoleReadNumE			varXLow, L7
			mov						al,varXLow
			mov						varXHigh,al
			ret
AskVars		ENDP


;-------------------------------------------------------------------------------------------------
CalculateY	PROC
;  
; Lasketaan annettujen arvojen mukaan Y:n arvot kun y=kx+b.
;-------------------------------------------------------------------------------------------------

			Nollaa					ecx						; nollataan ecx
			cmp						varKulma,0				; jos kulmakerroin on 0
			je						LINE					; piirret��n pelkk� suora
			mov						cl, varXLow				; asetetaan laskurille x:n yl�raja
L1:			mov						varXLow,cl				; juokseva x talteen
			push					ecx						; laitetaan laskuri pinoon, koska ecx rekisteri voi muuttua
			mov						counter, cl				; otetaan laskurin kuluva arvo talteen, k�ytet��n X-asettamiseen
			FunctionY				varKulma,varXLow,\		; lasketaan Y	
									varVakio,varY
													
L5:			mov						al,previousY			; lineaarinen funktio y=kx+b, voidaan
			sub						al,varY					; laskea suoraan y-askeleet funktioiden erotuksesta
			js						L3						; hyp�t��n jos al on negatiivinen
			ConsoleWriteEmptyY		al						; siirryt��n y-erotusten verran alasp�in konsolissa

L3:			cmp						counter,0
			je						L4
			ConsoleWriteEmptyX		counter					; siirryt��n kuluvan x:n verran konsolissa oikealle
L4:			ConsoleWriteChar 'x'

			mov						al,varY					; otetaan edellinen Y talteen			
			mov						previousY,al			
			pop						ecx						; pinosta laskurin arvo ulos
			cmp						ecx,0					; jos zero lippu p��ll� niin 
			jz						QUIT					; lopetetaan laskenta
			dec						ecx						; muutoin v�hennet��n laskurin arvoa
			jmp						L1						; ja hyp�t��n takaisin L1:een

LINE:		ConsoleWriteChars		'x',varXHigh			; kulmakerroin=0, piirret��n suora		
QUIT:
			ConsoleWriteString		dashLine
			ret
CalculateY	ENDP


;-------------------------------------------------------------------------------------------------
AskAgain		PROC
;  
; Kysyy k�ytt�j�lt� piirret��nk� uudelleen
;------------------------------------------------------------------------------------------------
			ConsoleWriteString		promptUud
			call _getchar 
			cmp eax,'k'
			je L0											; jos 'k' niin kutsutaan p��ohjelmaa
			jmp QUIT
L0:			EatEnter										; sy� seuraavan merkin									
			call _main
QUIT:		ret
AskAgain	ENDP
			end
