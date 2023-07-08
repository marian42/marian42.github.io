from mistune import HTMLRenderer
import shutil
import os

from config import OUTPUT_DIRECTORY, SITE_URL
import templates
from media import get_media_from_cache

def make_url_global(url):
    if '://' in url:
        return url
    if not url.startswith("/"):
        url = "/" + url
    url = SITE_URL + url
    return url

class CustomHTMLRenderer(HTMLRenderer):
    def __init__(self, article, use_relative_image_urls=True):
        super().__init__(escape=False)
        self.article = article
        self.use_relative_image_urls = use_relative_image_urls
        self.use_global_urls = False
        
    def image(self, alt, url, title=None):
        global image_cache

        image = get_media_from_cache(self.article, url)

        if image.is_video:
            src = image.get_source(self.use_relative_image_urls)
            if self.use_global_urls and not self.use_relative_image_urls:
                src = make_url_global(url)
            return templates.video.render(src=src)
        else:
            url = image.get_link(self.use_relative_image_urls)
            src = image.get_source(self.use_relative_image_urls)
            if self.use_global_urls and not self.use_relative_image_urls:
                url = make_url_global(url)
                src = make_url_global(src)
        return templates.image.render(url=url, src=src, alt=alt)
    
    def link(self, text, url, title=None):
        if (url.startswith(self.article.url)):
            local_filename = url[len(self.article.url):]
            source_path = os.path.join(self.article.directory, local_filename)
            destination_path = os.path.join(OUTPUT_DIRECTORY, self.article.url[1:], local_filename)
            if not os.path.isfile(destination_path):
                shutil.copy(source_path, destination_path)

        if self.use_global_urls:
            url = make_url_global(url)

        return super().link(text, url, title)