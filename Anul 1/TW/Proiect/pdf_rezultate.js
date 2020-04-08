const puppeteer = require('puppeteer');
const fs = require('fs');

async function GetPdf(p, b, g) {
    const browser = await puppeteer.launch({ headless: true });
    const page = await browser.newPage();
    
    const contentHtml = fs.readFileSync('./rezultate.html', 'utf8');
    await page.setContent(contentHtml);    
    await page.evaluate(async (p, b, g) => {
        Complete(new pacient(p), new bilet(b), g);
        await Promise.all(Array.from(document.getElementsByTagName('img'), image => {
            if (image.complete) {
              return;
            }
            return new Promise((resolve, reject) => {
              image.addEventListener('load', resolve);
              image.addEventListener('error', reject);
            });
          }));
    }, p, b, g);

    const pdf = await page.pdf({ format: 'A4', displayHeaderFooter:true, headerTemplate:'<url>Test</url>' });
    browser.close();
    return pdf;
  }

  module.exports.GetPdf = GetPdf;