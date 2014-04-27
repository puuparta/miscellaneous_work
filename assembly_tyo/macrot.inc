.NOLIST

;------------------------------------------------------
ConsoleWriteEmptyX MACRO times
;  
; Etenee konsolissa times-parametrin verran oikealle.
; Times-parametri kuvaa välilyönnin-painalluksia.
; Käytetään asettamaan X-askelin steppejä.
;----------------------------------------------------
	xor ecx,ecx
	mov cl,times
	startX:
		push ecx
		mov eax,oneSpace
		push eax
		call _putchar
		pop eax
		pop ecx
	loop startX
ENDM

;------------------------------------------------------
ConsoleWriteChars MACRO char,times
;  
; Piirtää parametrina tulevan merkin times-kertaa
; samalle riville. Käytetään vaakasuoran viivan 
; piirtoon kun kulmakerroin=0
;---------------------------------------------------
	xor ecx,ecx
	mov cl,times
	startDot:
		push ecx
		mov eax,char
		push eax
		call _putchar
		pop eax
		pop ecx
	loop startDot
ENDM

;------------------------------------------------------
ConsoleWriteEmptyY MACRO times
;  
; Hyppää konsolissa times-parametrin verran alaspäin.
; Times-parametri kuvaa ENTER:n painalluksia.
; Käytetään asettamaan Y-akselin steppejä
;-----------------------------------------------------
	xor ecx,ecx
	mov cl,times
	startY:
		push ecx
		mov eax,13
		push eax
		call _putchar
		pop eax
		pop ecx
		push ecx
		mov eax,10
		push eax
		call _putchar
		pop eax
		pop ecx
	loop startY
ENDM

;------------------------------------------------------
ConsoleWriteChar MACRO merkki
;  
; Kirjoittaa merkin konsoliin.
;-----------------------------------------------------
	mov eax,merkki
	push eax
	call _putchar
	pop eax
ENDM

;------------------------------------------------------
ConsoleWriteNumber MACRO luku
;  
; Kirjoittaa numeron konsoliin.
; Lisää ascii-koodiin 48 eli '0' jotta numeron ascii
; koodi vastaa numeron arvoa
;-----------------------------------------------------
	add luku,'0'
	nollaa eax
	mov al,luku
	push eax
	call _putchar
	pop eax
ENDM

;------------------------------------------------------
ConsoleWriteReq MACRO req
;  
; Kirjoittaa parametrina tulevan rekisterin merkkinä
; konsoliin. Ei käytössä.
;-----------------------------------------------------
	mov eax,req
	push eax
	call _putchar
	pop eax
ENDM

;------------------------------------------------------
ConsoleWriteString MACRO teksti
;  
; Kirjoittaa konsoliin muuttujassa olevan tekstin
;-----------------------------------------------------
	mov eax, OFFSET teksti
	push eax
	call _puts
	pop eax
ENDM

LueMerkkiEAX MACRO merkki
	call _getchar ; tallettaa eax rekisteriin
ENDM

;------------------------------------------------------
ConsoleReadNumE MACRO muuttuja, LABEL
;  
; Lukee käyttäjän syötteeltä merkin.
; Tarkemmin sanottuna luvun 0-9. Jos luku on muuta
; niin palaa parametrina annettuun labeliin
;-----------------------------------------------------
	call _getchar ; tallettaa eax rekisteriin
	mov [muuttuja],al
	sub [muuttuja],'0'
	EatEnter
	cmp muuttuja,10
	jge LABEL
	cmp muuttuja,0
	jl LABEL
ENDM

;------------------------------------------------------
ConsoleReadNum MACRO muuttuja
;  
; Lukee käyttäjän syötteeltä merkin ja muuttaa
; numeroksi
;-----------------------------------------------------
	call _getchar ; tallettaa eax rekisteriin
	mov [muuttuja],al
	sub [muuttuja],'0'
	EatEnter
ENDM


;------------------------------------------------------
ConsoleReadChar MACRO LABEL
;  
; Lukee käyttäjän syötteeltä merkin.
;-----------------------------------------------------
	call _getchar ; tallettaa eax rekisteriin
	cmp eax,'k'
	EatEnter
	je LABEL
ENDM

;------------------------------------------------------
EatEnter MACRO
;  
; Syö enterin pois kun luetaan käyttäjältä syötettä.
; Käytetään ConsoleReadNum ja ConsoleReadChar-macroista.
;-----------------------------------------------------
	call _getchar ; tallettaa eax rekisteriin
ENDM

;------------------------------------------------------
Nollaa MACRO p1
;  
; nollaa rekisterin
;------------------------------------------------------
	xor p1,p1
ENDM


;------------------------------------------------------
Multiply MACRO p1,p2,v
;  
; Kertoo kaksi parametriä keskenään jotka voivat
; olla joko rekistereitä tai muuttujia.
; palauttaa vastaukseen v-parametriin
;----------------------------------------------------
	Nollaa eax
	mov al,p1
	mul p2
	mov v,al
ENDM

;------------------------------------------------------
FunctionY MACRO varKulma,x,varVakio,varY
;  
; Y:n funktio eli y=2x+b
; ottaa parametriksi kulmakertoimen, vakiotermin
; ja palauttaa vastauksen kolmanteen parametriin
;----------------------------------------------------
	Multiply varKulma,x,varY	; k*x=y
	Nollaa al
	mov al,varY					; vakiotermin lisäys
	add al,varVakio
	mov varY,al
ENDM
.LIST
