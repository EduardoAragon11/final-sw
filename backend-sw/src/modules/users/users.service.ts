import { Injectable } from '@nestjs/common';
import { UserEntity } from '../../types/user.type';
import { v4 as uuidv4 } from 'uuid';

const INITIAL_USERS: UserEntity[] = [
  { id: uuidv4(), username: 'admin', password: 'adminpass', roles: ['Admin'] },
  { id: uuidv4(), username: 'user', password: 'userpass', roles: ['User'] },
];

@Injectable()
export class UsersService {
  private users = [...INITIAL_USERS];

  findByUsername(username: string) {
    return this.users.find((u) => u.username === username);
  }

  validateCredentials(username: string, password: string) {
    const user = this.findByUsername(username);
    if (!user) return null;
    return user.password === password ? user : null;
  }
}
