from locust import HttpUser, task

class WebsiteUser(HttpUser):
    @task
    def load_main_page(self):
        self.client.get("/index.html")

    # @task
    # def load_not_found_page(self):
    #     self.client.get("/notfound.html")

    @task
    def load_second_page(self):
        self.client.get("/page2.html")

