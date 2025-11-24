import { Test, TestingModule } from '@nestjs/testing';
import { INestApplication } from '@nestjs/common';
import request from 'supertest';
import { AppModule } from '../../src/app.module';

describe('Users E2E', () => {
  let app: INestApplication;

  beforeAll(async () => {
    const module: TestingModule = await Test.createTestingModule({
      imports: [AppModule],
    }).compile();

    app = module.createNestApplication();
    await app.init();
  });

  afterAll(async () => {
    await app.close();
  });

  it('validate correct credentials', async () => {
    const res = await request(app.getHttpServer())
      .post('/auth/login')
      .send({ username: 'user', password: 'userpass' })
      .expect(201);

    expect(res.body.access_token).toBeDefined();
  });
});
