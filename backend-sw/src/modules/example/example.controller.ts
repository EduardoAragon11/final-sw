import { Controller, Get, Req, UseGuards } from "@nestjs/common";
import { ExampleService } from "./example.service";
import { JwtAuthGuard } from "../../core/guards/jwt-auth.guard";
import { RolesGuard } from "../../core/guards/roles.guard";
import { RolesAllowed } from "../../core/decorators/roles.decorator";
import { Roles } from "../../core/constants/roles";

@Controller("example")
export class ExampleController {
  constructor(private svc: ExampleService) {}

  @Get("public")
  getPublic() {
    return this.svc.getPublic();
  }

  @UseGuards(JwtAuthGuard)
  @Get("protected")
  getProtected(@Req() req: any) {
    return this.svc.getProtected(req.user.username);
  }

  @UseGuards(JwtAuthGuard, RolesGuard)
  @RolesAllowed(Roles.ADMIN)
  @Get("admin")
  getAdmin(@Req() req: any) {
    return this.svc.getAdmin(req.user.username);
  }
}
