; ----------------------------------------------------------------------------
; viivanyhtalo.asm
; 10.03.2014, P. Heinonen
;
; Harjoitustyö Käskykieli 132C1 2013-2014 opintojakso, INTKAI10X2
;
; Win32 konsolisovellus Assembly-kielellä joka piirtää
; viivan X-merkeillä kun käyttäjä syöttää 
; kulmakertoimen, vakiotermin ja x:n ylärajan.
; Tämä kuvaa ensimmäistä versiota jossa
; sallittu syötealue on rajattu välille: 0-9
; x:n alin arvo on 0 ja ylin arvo käyttäjän antama 0-9
; Koordinaatiston akseleiden "piirtämisen" jätin pois.
;
; Prosessori: 386 tai uudempi
; Kääntäjä: MASM/ML
; OS: Win32/Win64
;
; Sisennyksessä käytetään sekoitusta Microsoftin coding conventionista
; ja Irvine32 assembly-kirjastosta. Labelointi ja macron ja proseduurien
; otsikkokommentointi on Irvine32 mukainen.
; Irvine32 kirjastosta saisi myös värit mukaan konsolille. En ottanut
; käyttöön. Includella testasin väritystä ja hyvin toimi.
; 
; Komentoriviltä käännös: "ml hello.asm /c"
; Komentoriviltä linkkaus: "link hello kernel32.lib mvcrt.lib 
; lisäoptio jos haluaa _main sijasta käyttää 
; omaa entrypointia: /subsystem:console /entry:letsGo"
; ----------------------------------------------------------------------------

		
		.586
		.model flat
		EXTERN _puts:near
		EXTERN _putchar:near
		EXTERN _getchar:near
		;public _letsGo			; tällä voi korvata _main-PROCin mikäli entry-asetetaan.
								; Koin paremmaksi käyttää _main:ia sillä VS2012 debuggeri
								; ei näyttänyt saavan breakpointeja toimimaan 
								; kustomoituun entrypointiin

		include macrot.inc		; makrot syötteiden käsittelyyn
		



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


			.stack	; ei välttämätön

;-------------------------------------------------------------------------------------------------
;                      PUBLIC PROCEDURES                                                         -
;-------------------------------------------------------------------------------------------------

			.CODE

;-------------------------------------------------------------------------------------------------
_main		PROC
;  
; Pääohjelma. Kutsuu aliohjelmia joilla kysytään käyttäjän syötteitä 
; ja lasketaan Y:n arvot.
;-------------------------------------------------------------------------------------------------

L0:			Nollaa					eax						; nollataan eax rekisteri varmuuden 
															; vuoksi.
			call					AskVars					; luetaan käyttäjän syötteet muuttujiin
			
			call					CalculateY				; piirretään y:n kuvaaja
															; ei käytetä loop-operaattoria, 
															; koska joudutaan pilkkomaan 
															; koodiblokkeja turhaan - "long jump"-ongelma.
															; jossakin väitettiin, että silmukka 
															; suoriutuu nopeammin ilman loop-operaatiota, 
															; tiedä sitten, en vertaillut sen enempää.
			call					AskAgain				; Kysytään piirretäänkö uudelleen		
			ret
_main		ENDP

;-------------------------------------------------------------------------------------------------
AskVars		PROC
;  
; Kysyy käyttäjältä syötteet ja asettaa ne muuttujiin
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
			je						LINE					; piirretään pelkkä suora
			mov						cl, varXLow				; asetetaan laskurille x:n yläraja
L1:			mov						varXLow,cl				; juokseva x talteen
			push					ecx						; laitetaan laskuri pinoon, koska ecx rekisteri voi muuttua
			mov						counter, cl				; otetaan laskurin kuluva arvo talteen, käytetään X-asettamiseen
			FunctionY				varKulma,varXLow,\		; lasketaan Y	
									varVakio,varY
													
L5:			mov						al,previousY			; lineaarinen funktio y=kx+b, voidaan
			sub						al,varY					; laskea suoraan y-askeleet funktioiden erotuksesta
			js						L3						; hypätään jos al on negatiivinen
			ConsoleWriteEmptyY		al						; siirrytään y-erotusten verran alaspäin konsolissa

L3:			cmp						counter,0
			je						L4
			ConsoleWriteEmptyX		counter					; siirrytään kuluvan x:n verran konsolissa oikealle
L4:			ConsoleWriteChar 'x'

			mov						al,varY					; otetaan edellinen Y talteen			
			mov						previousY,al			
			pop						ecx						; pinosta laskurin arvo ulos
			cmp						ecx,0					; jos zero lippu päällä niin 
			jz						QUIT					; lopetetaan laskenta
			dec						ecx						; muutoin vähennetään laskurin arvoa
			jmp						L1						; ja hypätään takaisin L1:een

LINE:		ConsoleWriteChars		'x',varXHigh			; kulmakerroin=0, piirretään suora		
QUIT:
			ConsoleWriteString		dashLine
			ret
CalculateY	ENDP


;-------------------------------------------------------------------------------------------------
AskAgain		PROC
;  
; Kysyy käyttäjältä piirretäänkö uudelleen
;------------------------------------------------------------------------------------------------
			ConsoleWriteString		promptUud
			call _getchar 
			cmp eax,'k'
			je L0											; jos 'k' niin kutsutaan pääohjelmaa
			jmp QUIT
L0:			EatEnter										; syö seuraavan merkin									
			call _main
QUIT:		ret
AskAgain	ENDP
			end
