import os
import shutil
import math
from datetime import datetime
import html
import re
import urllib.parse
import sys

from article import Article
import config
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

def write_file(filename, html_content):    
    if filename.startswith("/"):
        filename = filename[1:]
    if not filename.endswith('.html') and not filename.endswith('.xml'):
        filename = os.path.join(filename, "index.html")
    filename = os.path.join(OUTPUT_DIRECTORY, filename)
    file_directory = os.path.dirname(filename)
    if not os.path.isdir(file_directory):
        os.makedirs(file_directory)
    with open(filename, 'w', encoding='utf8') as file:
        file.write(html_content)

def render_404_page():
    not_found_title = "404 Page not found"
    not_found_content = "The requested page was not found."
    not_found_url = "/404.html"
    output = templates.page.render(
        content=templates.article.render(
            content=not_found_content,
            title=not_found_title,
            url=not_found_url
        ),
        title=not_found_title + " | " + config.SITE_TITLE,
        name=not_found_title,
        description=not_found_title + " - " + config.SITE_SUBTITLE,
        url=config.SITE_URL + not_found_url,
        site_name=config.SITE_TITLE,
        author=config.AUTHOR,
        site_url=config.SITE_URL
    )
    write_file(not_found_url, output)

def create_redirect(source, destination):
    write_file(source, templates.redirect.render(url=config.SITE_URL + destination))

def create_rss_feed(articles):
    rss_items = []
    for article in articles:
        content = templates.rss_article.render(
            content=html.escape(article.get_html_content(use_global_urls=True)),
            title=article.title,
            time=article.date.strftime(config.RSS_DATE_FORMAT),
            url=config.SITE_URL + article.url
        )
        rss_items.append(content)

    write_file('index.xml', templates.rss_feed.render(
        description=config.SITE_SUBTITLE,
        site_name=config.SITE_TITLE,
        site_url=config.SITE_URL,
        time=datetime.now().strftime(config.RSS_DATE_FORMAT),
        rss_url=config.SITE_URL + '/index.xml',
        articles="\n".join(rss_items)
    ))

def create_style():
    content = open('theme/style.css', 'r').read()
    pattern = r'url\(\"(.*\.svg)\"\);'

    for filename in re.findall(pattern, content):
        svg_content = open(os.path.join('theme', filename)).read()
        result = 'data:image/svg+xml,' + urllib.parse.quote(svg_content, safe='~()*!\'')
        content = content.replace(filename, result)

    with open(os.path.join(config.OUTPUT_DIRECTORY, 'style.css'), 'w', encoding='utf8') as file:
        file.write(content)

def create_feed(articles):
    page_count = math.ceil(len(articles) / ARTICLES_PER_PAGE)
    page_urls = ['/page/' + str(i + 1) for i in range(page_count)]
    page_urls[0] = '/'

    for page_index in range(page_count):
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

        page_html = templates.page.render(
            content=cards_html,
            title=config.SITE_TITLE,
            name=config.SITE_TITLE,
            description=config.SITE_SUBTITLE,
            url=config.SITE_URL + page_urls[page_index],
            site_name=config.SITE_TITLE,
            author=config.AUTHOR,
            site_url=config.SITE_URL
        )
        write_file(page_urls[page_index], page_html)

def create_article(article):
    output = templates.page.render(
        content=templates.article.render(
            content=article.get_html_content(),
            title=article.title,
            time=article.date.strftime(DATE_FORMAT),
            url=article.url
        ),
        title=article.title + " | " + config.SITE_TITLE,
        name=article.title,
        description=article.title + " - " + config.SITE_SUBTITLE,
        url=config.SITE_URL + article.url,
        site_name=config.SITE_TITLE,
        author=config.AUTHOR,
        site_url=config.SITE_URL,
        image=(config.SITE_URL + article.article_image) if article.article_image is not None else ''
    )
    write_file(article.url, output)

def generate_site():
    if not os.path.exists(OUTPUT_DIRECTORY):
        os.makedirs(OUTPUT_DIRECTORY)

    if not FAST:
        clear_directory(OUTPUT_DIRECTORY)
    
    copy_content('theme/static', OUTPUT_DIRECTORY)

    articles = []

    for article_folder in os.listdir(ARTICLES_DIRECTORY):
        article_path = os.path.join(ARTICLES_DIRECTORY, article_folder)
        if not os.path.isfile(os.path.join(article_path, 'index.md')):
            continue
        article = Article(article_path)
        articles.append(article)

    articles.sort(key=lambda article: article.date, reverse=True)

    create_feed(articles)

    for article in articles:
        create_article(article)        

    render_404_page()

    create_redirect("page/1", "/")

    create_rss_feed(articles)

    create_style()

print("Generating site...")
generate_site()

if '--watch' in sys.argv:
    print("Site generated. Waiting for changes.")

    from watchdog.observers import Observer
    from watchdog.events import FileSystemEventHandler
    import time

    last_update = datetime.now()

    class FileChangeHandler(FileSystemEventHandler):
        def __init__(self, callback):
            self.callback = callback

        def on_modified(self, event):
            self.callback()

        def on_created(self, event):
            self.callback()

    def on_folder_changed():
        global last_update
        if (datetime.now() - last_update).total_seconds() < 2:
            return

        print("Files have changed. Regenerating site...")
        generate_site()
        print("Done. Waiting for changes.")

        last_update = datetime.now()

    observer1 = Observer()
    observer1.schedule(FileChangeHandler(callback=on_folder_changed), 'theme', recursive=True)
    observer1.start()
    observer2 = Observer()
    observer2.schedule(FileChangeHandler(callback=on_folder_changed), 'content', recursive=True)
    observer2.start()

    try:
        while True:
            time.sleep(0.1)
    except KeyboardInterrupt:
        observer1.stop()
        observer2.stop()

    observer1.join()
    observer2.join()