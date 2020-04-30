### Site Laborator de analize medicale

### Proiect (maxim 30 puncte)

**Tema:** Construiti o aplicatie web care respecte criteriile de acceptanta si cerintele de mai jos. Tematica site-ului este la libera alegere.

**Criterii de acceptanta:**

- aplicatia sa fie [Single Page Application](https://en.wikipedia.org/wiki/Single-page_application) ✔
- codul sursa (nearhivat) al proiectului trebuie sa fie salvat pe [GitHub](https://github.com/) ✔
- nu puteti folosi librarii, framework-uri [CSS](https://en.wikipedia.org/wiki/CSS_framework) sau [JavaScript](https://en.wikipedia.org/wiki/JavaScript_framework) (cum ar fi jQuery, Bootstrap, Angular, React, etc) pentru realizarea frontend-ului ✔

> **Atentie!** Orice proiect care nu respecta criteriile de acceptanta este evaluat la 0 puncte. 

#### Frontend (maxim 17 puncte)

##### HTML si CSS (maxim 8 puncte)

- Fisiere separate pentru HTML si CSS (0.5 puncte) ✔
- In interiorul documentelor HTML, sa se foloseasca minim 4 [taguri semantice]  (https://www.w3schools.com/html/html5_semantic_elements.asp) (1 punct) ✔
```html
<header>, <nav>, <main>, <aside>, <footer> 
```
Link: [index.html](public/index.html)
- Stilurile CSS sa fie definite folosind clase direct pe elementele care trebuie stilizate (minim 80% din selectori) (0.5 punct) ✔

Link: [style.css](public/css/style.css)
- Layout-ul sa fie impartit in minim 2 coloane si sa fie realizat cu [Flexbox](https://css-tricks.com/snippets/css/a-guide-to-flexbox/) ✔ si/sau [CSS grid](https://css-tricks.com/snippets/css/complete-guide-grid/) (2 puncte)

Link: [style.css](public/css/style.css)
- Site-ul sa fie [responsive](https://www.w3schools.com/html/html_responsive.asp), respectand rezolutiile urmatoarelor dispozitive folosind [media queries](https://www.uxpin.com/studio/blog/media-queries-responsive-web-design/): (4 puncte) ✔
  - telefon mobil - latime mai mica 768px
  - tableta - latime intre 768px si 1280px
  - desktop - latime mai mare de 1280px
  
Link: [style.css](public/css/style.css)

##### Javascript (maxim 9 puncte)

- Fisier separat JavaScript (0.5 puncte) ✔
- Manipularea DOM-ului (crearea, editarea si stergerea elementelor/nodurilor HTML) (3 puncte) ✔

Link: [modalBox.js](public/js/modalBox.js), [starRating.js](public/js/starRating.js)
- Folosirea evenimentelor JavaScript declansate de mouse/tastatura (1 punct) ✔

Link: [modalBox.js](public/js/modalBox.js), [starRating.js](public/js/starRating.js)
- Utilizarea [AJAX](https://www.w3schools.com/xml/ajax_intro.asp) ([GET, POST, PUT, DELETE]  (http://www.restapitutorial.com/lessons/httpmethods.html)) (4 puncte) ✔ 

Link: [index.js](public/js/index.js)
- Folosirea localStorage (0.5 puncte) ✔ 

Link: [index.js](public/js/index.js)

#### Backend API (maxim 8 puncte)

- Creare server Backend (2 puncte) ✔ 

Link: [index.js](app.js)
- CRUD API (Create, Read, Update si Delete) pentru a servi Frontend-ului (6 puncte) ✔ 

Link: [index.js](app.js)

#### Punctaj subiectiv (maxim 5 puncte)

Ne vom imagina ca aplicatia trebuie prezentata unui client, care va aprecia, de exemplu:

- calitatea sustinerii prezentarii proiectului
- designul (sa arate placut si ingrijit)
- utilitatea (sa rezolve probleme reale)
- stabilitatea (sa NU contina defecte evidente)
- complexitatea (sa aiba mai multe ecrane, layout-ul sa fie mai complex etc.)
