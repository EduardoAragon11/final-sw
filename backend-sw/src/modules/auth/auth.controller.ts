import { Controller, Post, Body } from "@nestjs/common";
import { LoginDto } from "../users/dtos/login.dto";
import { AuthService } from "./auth.service";

@Controller("auth")
export class AuthController {
  constructor(private auth: AuthService) {}

  @Post("login")
  async login(@Body() dto: LoginDto) {
    const user = await this.auth.validateUser(dto.username, dto.password);
    return this.auth.login(user);
  }
}
