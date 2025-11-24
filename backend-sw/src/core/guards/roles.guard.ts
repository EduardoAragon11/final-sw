import { Injectable, CanActivate, ExecutionContext } from "@nestjs/common";
import { Reflector } from "@nestjs/core";

@Injectable()
export class RolesGuard implements CanActivate {
  constructor(private reflector: Reflector) {}

  canActivate(context: ExecutionContext): boolean {
    const required = this.reflector.getAllAndOverride<string[]>("roles", [
      context.getHandler(),
      context.getClass()
    ]);

    if (!required) return true;

    const request = context.switchToHttp().getRequest();
    const user = request.user;
    if (!user?.roles) return false;

    const roles = Array.isArray(user.roles) ? user.roles : [user.roles];
    return required.some((role) => roles.includes(role));
  }
}
