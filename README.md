# ProiectSA

Pe parcursul testării și rulării experimentelor pe diferite seturi de date (de la 10 la sute de mii de elemente), am observat câteva comportamente fascinante și, uneori, surprinzătoare ale algoritmilor de sortare. Iată cele mai importante concluzii:

1. Iluzia seturilor mici de date și „prăpastia” de performanță
La teste cu N=100 sau chiar 1.000 de elemente, toți algoritmii par la fel de buni, terminând în sub o milisecundă. Totuși, surpriza a apărut la trecerea de la 10.000 la 100.000 de elemente. Algoritmii simpli (Bubble, Insertion, Selection) nu au durat de 10 ori mai mult, ci de 100 de ori mai mult. Este o demonstrație practică brutală a complexității pătratice. În timp ce Bubble Sort „îngheață” programul pentru zeci de secunde pe o listă mare, Merge Sort și Quick Sort o rezolvă într-o fracțiune de secundă.

2. Călcâiul lui Ahile pentru Quick Sort (și cum a fost reparat)
Teoretic, Quick Sort este cel mai rapid algoritm general. Însă, testele pe liste deja sortate sau invers sortate au scos la iveală o vulnerabilitate majoră. Dacă pivotul ales este mereu ultimul element (cum se predă adesea în forma de bază), algoritmul devine la fel de lent ca Bubble Sort și, mai grav, poate da Stack Overflow (eroare de memorie) pe liste mari din cauza recursivității excesive. Soluția pe care am implementat-o – alegerea pivotului de la mijlocul listei – a stabilizat complet performanța, transformând cazul defavorabil într-unul favorabil.

3. „Puterea ascunsă” a lui Insertion Sort
Deși aparține categoriei de algoritmi lenți, Insertion Sort a generat o surpriză plăcută în scenariul listelor aproape sortate (liste cu doar 5% din elemente amestecate). În acest caz specific, Insertion Sort a terminat aproape instantaneu, surclasând chiar și algoritmi complecși precum Merge Sort. Acest lucru dovedește că algoritmul este extrem de inteligent când vine vorba de a recunoaște elementele care sunt deja la locul lor.

4. Magia din spatele Shell Sort
Shell Sort a fost puntea perfectă de legătură între metodele simple și cele avansate. Deși implementarea sa este doar o mică modificare a lui Insertion Sort (folosind "sărituri" / gap-uri în loc să compare doar vecinii), diferența de viteză este uluitoare. Pe liste de zeci de mii de elemente aleatorii, Shell Sort ține pasul admirabil cu coloșii Quick și Merge Sort, neavând nevoie de funcții recursive complicate sau memorie suplimentară.

5. Selecția ignoră ordinea inițială
Un detaliu interesant observat la Selection Sort este „încăpățânarea” lui. Indiferent dacă lista de test a fost generată complet aleatoriu, gata sortată, invers sortată sau plată, Selection Sort a scos mereu același timp de execuție. El nu profită deloc de ordinea existentă a datelor, fiind nevoit să scaneze mereu toată porțiunea rămasă pentru a găsi minimul.
