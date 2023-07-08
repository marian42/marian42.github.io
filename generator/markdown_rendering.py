from mistune import HTMLRenderer
import shutil
import os

from config import OUTPUT_DIRECTORY
import templates
from media import get_media_from_cache

class CustomHTMLRenderer(HTMLRenderer):
    def __init__(self, article, use_relative_image_urls=True):
        super().__init__(escape=False)
        self.article = article
        self.use_relative_image_urls = use_relative_image_urls
        
    def image(self, alt, url, title=None):
        global image_cache

        image = get_media_from_cache(self.article, url)

        if image.is_video:
            return templates.video.render(src=image.get_source(self.use_relative_image_urls))
                
        return templates.image.render(url=image.get_link(self.use_relative_image_urls), src=image.get_source(self.use_relative_image_urls), alt=alt)
    
    def link(self, text, url, title=None):
        if (url.startswith(self.article.url)):
            local_filename = url[len(self.article.url):]
            source_path = os.path.join(self.article.directory, local_filename)
            destination_path = os.path.join(OUTPUT_DIRECTORY, self.article.url[1:], local_filename)
            if not os.path.isfile(destination_path):
                shutil.copy(source_path, destination_path)

        return super().link(text, url, title)