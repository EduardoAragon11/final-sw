import { Injectable } from "@nestjs/common";

@Injectable()
export class ExampleService {
  getPublic() {
    return { message: "This is a public endpoint" };
  }

  getProtected(username: string) {
    return { message: `Hello ${username}, you are authenticated.` };
  }

  getAdmin(username: string) {
    return { message: `Welcome Admin ${username}` };
  }
}
