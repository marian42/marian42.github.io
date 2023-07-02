import os
import shutil
import math
from tqdm import tqdm

from article import Article

from config import OUTPUT_DIRECTORY, FAST, ARTICLES_DIRECTORY, ARTICLES_PER_PAGE, DATE_FORMAT

import templates

def clear_directory(directory):
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)

        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)

def copy_content(source_directory, destination_directory):
    for item_name in os.listdir(source_directory):
        shutil.copy(os.path.join(source_directory, item_name), os.path.join(destination_directory, item_name))

def write_file(filename, content):
    if filename.startswith("/"):
        filename = filename[1:]
    if not filename.endswith('.html'):
        filename = os.path.join(filename, "index.html")
    filename = os.path.join(OUTPUT_DIRECTORY, filename)
    file_directory = os.path.dirname(filename)
    if not os.path.isdir(file_directory):
        os.makedirs(file_directory)
    with open(filename, 'w', encoding='utf8') as file:
        file.write(content)


if not os.path.exists(OUTPUT_DIRECTORY):
    os.makedirs(OUTPUT_DIRECTORY)

if not FAST:
    clear_directory(OUTPUT_DIRECTORY)
copy_content('theme/static', OUTPUT_DIRECTORY)

articles = []

for article_folder in os.listdir(ARTICLES_DIRECTORY):
    article_path = os.path.join(ARTICLES_DIRECTORY, article_folder)
    article = Article(article_path)
    articles.append(article)

articles.sort(key=lambda article: article.date, reverse=True)

page_count = math.ceil(len(articles) / ARTICLES_PER_PAGE)
page_urls = ['/page/' + str(i + 1) for i in range(page_count)]
page_urls[0] = '/'

print(len(articles), "articles on", page_count, "pages")

for page_index in tqdm(range(page_count), desc="Feed"):
    page_articles = articles[page_index * ARTICLES_PER_PAGE : (page_index + 1) * ARTICLES_PER_PAGE]

    cards_html = [
        templates.article_summary.render(
            content=article.get_html_summary(),        
            title=article.title,
            time=article.date.strftime(DATE_FORMAT),
            url=article.url
        )
        for article in page_articles
    ]

    navigation = '<div class="page-navigation">\n'
    if page_index != page_count - 1:
        navigation += '<a href="' + page_urls[page_index + 1] + '">see older posts</a>\n'
    if page_index != 0:
        navigation += '<a href="' + page_urls[page_index - 1] + '">see newer posts</a>\n'
    navigation += '</div>'
    cards_html.append(navigation)

    cards_html = '\n\n'.join(cards_html)

    page_html = templates.page.render(content=cards_html)
    write_file(page_urls[page_index], page_html)

for article in tqdm(articles, desc="Articles"):
    output = templates.page.render(
        content=templates.article.render(
            content=article.get_html_content(),        
            title=article.title,
            time=article.date.strftime(DATE_FORMAT),
            url=article.url
        )
    )
    write_file(article.url, output)